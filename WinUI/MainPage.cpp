#include "pch.h"

#include "MainPage.h"
#include "MainPage.g.cpp"

#include <format>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::ViewManagement;
using namespace Windows::ApplicationModel::Core;

namespace winrt::RTX_2090_TiFy::implementation {

MainPage::MainPage() {
    InitializeComponent();

    auto titleBar = ApplicationView::GetForCurrentView().TitleBar();
    titleBar.ButtonBackgroundColor(Colors::Transparent());

    titleBar.ButtonInactiveBackgroundColor(Colors::Transparent());

    // Hide Default Title Bar
    auto coreTitleBar = CoreApplication::GetCurrentView().TitleBar();
    coreTitleBar.ExtendViewIntoTitleBar(true);

    // Set XAML element as a draggable region
    Window::Current().SetTitleBar(AppTitleBar());

#ifdef _DEBUG
    AppTitle().Text(AppTitle().Text() + L" (DEBUG Edition)");
#endif
}

int32_t MainPage::MyProperty() { throw hresult_not_implemented(); }

void MainPage::MyProperty(int32_t) { throw hresult_not_implemented(); }

IAsyncAction MainPage::SelectInput_Click(IInspectable const& sender,
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

    auto file = co_await picker.PickSingleFileAsync();

    if (!file) co_return;

    auto previewImg = Imaging::BitmapImage();

    auto imgStream = co_await file.OpenAsync(FileAccessMode::Read);
    co_await previewImg.SetSourceAsync(imgStream);

    InputImage().Source(previewImg);
}

Windows::Foundation::IAsyncAction MainPage::SelectOutput_Click(
    IInspectable const& sender, RoutedEventArgs const& e) {
    using namespace Windows::Storage::Pickers;
    auto picker = FileSavePicker();
    picker.SuggestedStartLocation(PickerLocationId::PicturesLibrary);
    picker.FileTypeChoices().Insert(L"MP4",
                                    single_threaded_vector<hstring>({L".mp4"}));

    auto file = co_await picker.PickSaveFileAsync();

    if (!file) co_return;

    OutputText().Text(L"Output Path: " + file.Path());
}

IAsyncAction MainPage::License_Click(IInspectable const&,
                                     RoutedEventArgs const&) {
    using namespace Windows::Storage;

    auto dialog = ContentDialog();
    dialog.Title(box_value(L"MIT License"));
    dialog.DefaultButton(ContentDialogButton::Close);
    dialog.CloseButtonText(L"Close");

    auto license = co_await FileIO::ReadTextAsync(
        co_await StorageFile::GetFileFromApplicationUriAsync(
            Uri(L"ms-appx:///LICENSE.g.txt")));

    dialog.Content(box_value(license));

    co_await dialog.ShowAsync();
}

IAsyncAction MainPage::VisitSite_Click(IInspectable const&,
                                       RoutedEventArgs const&) {
    co_await Windows::System::Launcher::LaunchUriAsync(
        Uri(L"https://github.com/Leomotors/RTX-2090-TiFy-2"));
}

IAsyncAction MainPage::About_Click(IInspectable const&,
                                   RoutedEventArgs const&) {
    auto dialog = ContentDialog();
    dialog.Title(box_value(L"About App"));
    dialog.DefaultButton(ContentDialogButton::Close);
    dialog.CloseButtonText(L"Close");

    auto version = Windows::ApplicationModel::Package::Current().Id().Version();

    auto vertext = std::format("{}.{} Build {}.{}", version.Major,
                               version.Minor, version.Build, version.Revision);

    auto content = std::format("App Version: {}", vertext);

    dialog.Content(box_value(to_hstring(content)));
    co_await dialog.ShowAsync();
}

}  // namespace winrt::RTX_2090_TiFy::implementation
