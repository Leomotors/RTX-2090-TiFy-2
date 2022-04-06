#include "pch.h"
#include "HomePage.h"
#if __has_include("HomePage.g.cpp")
#include "HomePage.g.cpp"
#endif

#include "AppState.hpp"

#include "GPUConfig.hpp"
#include "StringHelper.hpp"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::RTX_2090_TiFy::implementation {

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

    OutputFileName().PlaceholderText(to_hstring(
        RTXLib::StringHelper::removeFileExtension(to_string(file.Name()))));

    InputLoadProgress().Visibility(Visibility::Collapsed);
}

fire_and_forget HomePage::AdvancedSettings_Click(IInspectable const& sender,
                                                 RoutedEventArgs const& e) {
    using namespace Windows::UI::Xaml::Controls;

    WarpPointsTextBox().Text(
        to_hstring(AppState::GPUConfig.warpLocationsAsStr()));

    auto result = co_await AdvancedSettingsDialog().ShowAsync();

    if (result == ContentDialogResult::Primary) {
        AppState::GPUConfig.setWarpLocations(
            to_string(WarpPointsTextBox().Text()));
    }
}

void HomePage::GenWarp_Click(IInspectable const&,
                             RoutedEventArgs const&) {
    AppState::GPUConfig.resetWarpLocations();
    WarpPointsTextBox().Text(
        to_hstring(AppState::GPUConfig.warpLocationsAsStr()));
}

}  // namespace winrt::RTX_2090_TiFy::implementation
