#include "pch.h"
#include "Settings.h"
#if __has_include("Settings.g.cpp")
#include "Settings.g.cpp"
#endif

#include "AppConstants.hpp"
#include "AppSettings.hpp"
#include "ThemeColor.hpp"

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::RTX_2090_TiFy::implementation {

Settings::Settings() {
    InitializeComponent();

    auto version = Windows::ApplicationModel::Package::Current().Id().Version();

    auto vertext = std::format(L"Version: {}.{} Build {}.{}", version.Major,
                               version.Minor, version.Build, version.Revision);

    AppVersion().Text(vertext);
}

fire_and_forget Settings::License_Click(IInspectable const&,
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

void Settings::ThemeSelector_Loaded(IInspectable const& sender,
                                    RoutedEventArgs const&) {
    auto radio = sender.as<Microsoft::UI::Xaml::Controls::RadioButtons>();

    radio.SelectedIndex(AppSettings::CurrentTheme);
}

void Settings::Theme_SelectionChanged(IInspectable const& sender,
                                      SelectionChangedEventArgs const&) {
    using namespace Windows::Storage;
    auto settings = ApplicationData::Current().LocalSettings().Values();

    auto selected = sender.as<Microsoft::UI::Xaml::Controls::RadioButtons>()
                        .SelectedIndex();

    settings.Insert(AppSettings::Theme, box_value(selected));

    ThemeChangeAlert().IsOpen(selected != AppSettings::CurrentTheme);
}

void Settings::OpenTempFolder_Click(IInspectable const&,
                                    RoutedEventArgs const&) {
    auto folder =
        Windows::Storage::ApplicationData::Current().TemporaryFolder();
    Windows::System::Launcher::LaunchFolderAsync(folder);
}

fire_and_forget Settings::RickRollSwitch_Toggled(IInspectable const&,
                                                 ToggleSwitch const& e) {
    auto toggle = e;

    if (toggle.IsOn())
        co_await Windows::System::Launcher::LaunchUriAsync(
            Uri(AppConstants::URLToHeaven));

    toggle.IsOn(false);
    RickRollInfo().IsOpen(true);
}

fire_and_forget Settings::Restart_Click(IInspectable const& sender,
                                        RoutedEventArgs const& e) {
    using namespace Windows::ApplicationModel::Core;

    auto failure = co_await CoreApplication::RequestRestartAsync({});

    hstring reason;

    switch (failure) {
        case AppRestartFailureReason::RestartPending:
            ThemeChangeAlert().ActionButton().Content().as<Button>().Content(
                box_value(L"Restarting..."));
            co_return;
        case AppRestartFailureReason::NotInForeground:
            reason = L"Not In Foreground";
            break;
        case AppRestartFailureReason::InvalidUser:
            reason = L"Invalid User";
            break;
        case AppRestartFailureReason::Other:
            reason = L"Other";
            break;
        default:
            reason = L"Unexpected Value, you should not see this";
    }

    ThemeChangeInfoBar().Title(L"Cannot Restart");
    ThemeChangeInfoBar().Message(
        std::format(L"Failure Reason: {}, please restart manually", reason));
    ThemeChangeInfoBar().Severity(
        Microsoft::UI::Xaml::Controls::InfoBarSeverity::Error);
    ThemeChangeInfoBar().IsOpen(true);
}

}  // namespace winrt::RTX_2090_TiFy::implementation
