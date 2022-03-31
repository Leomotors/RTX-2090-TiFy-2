#include "pch.h"
#include "Settings.h"
#if __has_include("Settings.g.cpp")
#include "Settings.g.cpp"
#endif

#include <format>

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::RTX_2090_TiFy::implementation {

Settings::Settings() { InitializeComponent(); }

IAsyncAction Settings::License_Click(IInspectable const&,
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

IAsyncAction Settings::About_Click(IInspectable const&,
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
