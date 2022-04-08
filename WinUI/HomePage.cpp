﻿#include "pch.h"
#include "HomePage.h"
#if __has_include("HomePage.g.cpp")
#include "HomePage.g.cpp"
#endif

#include "AppState.hpp"

#include "GPUConfig.hpp"
#include "StringHelper.hpp"
#include "RayTracing.hpp"

#include <format>

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::RTX_2090_TiFy::implementation {

hstring HomePage::s_inputFileName;

HomePage::HomePage() {
    InitializeComponent();

    const auto& output = AppState::GPUConfig.output;
    OutputDimX().Value(output.dims.first);
    OutputDimY().Value(output.dims.second);
    OutputFPS().Value(output.fps);
    OutputLoopLen().Value(output.length);
    OutputLoopCount().Value(output.loops);

    for (const auto& [val, name] : RTXLib::AlgoEnumToString) {
        auto nameh = to_hstring(name);
        hstringToAlgorithm[nameh] = val;
        OutputAlgorithm().Items().Append(box_value(nameh));

        if (val == output.algo) {
            OutputAlgorithm().SelectedItem(box_value(nameh));
        }
    }
}

void HomePage::OnNavigatedTo(Navigation::NavigationEventArgs const&) {
    if (AppState::ImageHandler.image.empty()) {
        return;
    }

    InputImage().Source(Windows::UI::Xaml::Media::Imaging::BitmapImage(
        Uri(to_hstring(AppState::ImageHandler.path))));
    OutputFileName().PlaceholderText(s_inputFileName);
}

void HomePage::saveSettings() {
    auto& output = AppState::GPUConfig.output;
    output.dims.first = static_cast<int32_t>(OutputDimX().Value());
    output.dims.second = static_cast<int32_t>(OutputDimY().Value());
    output.fps = static_cast<int32_t>(OutputFPS().Value());
    output.length = OutputLoopLen().Value();
    output.loops = static_cast<int32_t>(OutputLoopCount().Value());
    output.algo =
        hstringToAlgorithm[OutputAlgorithm().SelectedItem().as<hstring>()];
}

fire_and_forget HomePage::SelectInput_Click(IInspectable const& sender,
                                            RoutedEventArgs const& e) {
    using namespace Windows::Storage;
    using namespace Windows::Storage::Pickers;
    using namespace Windows::UI::Xaml::Media;

    auto picker = FileOpenPicker();
    picker.ViewMode(PickerViewMode::Thumbnail);
    picker.SuggestedStartLocation(PickerLocationId::PicturesLibrary);
    picker.FileTypeFilter().Append(L".jpg");
    picker.FileTypeFilter().Append(L".jpeg");
    picker.FileTypeFilter().Append(L".png");

    InputLoadProgress().Visibility(Visibility::Visible);

    auto file = co_await picker.PickSingleFileAsync();

    if (!file) {
        InputLoadProgress().Visibility(Visibility::Collapsed);
        co_return;
    }

    auto folder = ApplicationData::Current().TemporaryFolder();

    auto localCopy = co_await file.CopyAsync(
        folder, file.Name(), NameCollisionOption::ReplaceExisting);

    InputImage().Source(Imaging::BitmapImage(Uri(localCopy.Path())));

    AppState::ImageHandler.loadImage(to_string(localCopy.Path()));

    auto phdText = to_hstring(
        RTXLib::StringHelper::removeFileExtension(to_string(file.Name())));
    OutputFileName().PlaceholderText(phdText);
    s_inputFileName = phdText;

    InputLoadProgress().Visibility(Visibility::Collapsed);
}

fire_and_forget HomePage::AdvancedSettings_Click(IInspectable const& sender,
                                                 RoutedEventArgs const& e) {
    saveSettings();
    AppState::GPUConfig.validateWarpLocations();

    WarpPointsTextBox().Text(
        to_hstring(AppState::GPUConfig.warpLocationsAsStr()));

    ValidateSuccessIcon().Visibility(Visibility::Collapsed);

    auto result = co_await AdvancedSettingsDialog().ShowAsync();

    if (result == ContentDialogResult::Primary) {
        AppState::GPUConfig.setWarpLocations(
            to_string(WarpPointsTextBox().Text()));
    }
}

void HomePage::WarpPointsTextBox_TextChanged(IInspectable const&,
                                             TextChangedEventArgs const&) {
    if (!verifyGuard) ValidateSuccessIcon().Visibility(Visibility::Collapsed);
    verifyGuard = false;
}

void HomePage::GenWarp_Click(IInspectable const&, RoutedEventArgs const&) {
    AppState::GPUConfig.resetWarpLocations();
    verifyGuard = true;
    WarpPointsTextBox().Text(
        to_hstring(AppState::GPUConfig.warpLocationsAsStr()));
    ValidateSuccessIcon().Visibility(Visibility::Visible);
}

void HomePage::Validate_Click(IInspectable const&, RoutedEventArgs const&) {
    AppState::GPUConfig.setWarpLocations(to_string(WarpPointsTextBox().Text()));
    verifyGuard = true;
    WarpPointsTextBox().Text(
        to_hstring(AppState::GPUConfig.warpLocationsAsStr()));
    ValidateSuccessIcon().Visibility(Visibility::Visible);
}

fire_and_forget HomePage::Generate_Click(IInspectable const&,
                                         RoutedEventArgs const&) {
    using namespace Windows::Storage;

    saveSettings();

    AppState::GPUConfig.validateWarpLocations();

    auto failReason = AppState::validate();
    if (failReason.has_value()) {
        NotRTXReadyTextBlock().Text(L"Failure Reason: " +
                                    to_hstring(failReason.value()));
        co_await NotRTXReadyDialog().ShowAsync();
        co_return;
    }

    auto tmpFolder = ApplicationData::Current().TemporaryFolder();
    auto outFolder = co_await tmpFolder.CreateFolderAsync(
        L"output", CreationCollisionOption::OpenIfExists);

    auto videoName = OutputFileName().Text();
    videoName =
        videoName.empty() ? OutputFileName().PlaceholderText() : videoName;
    auto videoPath = std::format(L"{}\\{}", outFolder.Path(), videoName);
    AppState::GPUConfig.output.path = to_string(videoPath);

    auto rayTracing =
        RTXLib::RayTracing(AppState::ImageHandler.image, AppState::GPUConfig);

    if (!rayTracing.outVideo.isOpened()) {
        auto dialog = ContentDialog();
        NotRTXReadyTextBlock().Text(
            L"Failure Reason: Cannot open Video Writer at " + videoPath +
            L".avi");
        co_await NotRTXReadyDialog().ShowAsync();
        co_return;
    }

    auto prom = RTXDialog().ShowAsync();

    while (true) {
        co_await winrt::resume_background();
        auto [curr, total] = rayTracing.NextFrame();
        co_await winrt::resume_foreground(RTXProgressBar().Dispatcher());

        RTXProgressText().Text(
            std::format(L"Generating... {}/{}", curr, total));
        RTXProgressBar().Value(100.0 * curr / total);

        if (curr >= total) break;
    }

    co_await prom;
}

}  // namespace winrt::RTX_2090_TiFy::implementation
