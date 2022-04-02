#include "pch.h"
#include "Settings.h"
#if __has_include("Settings.g.cpp")
#include "Settings.g.cpp"
#endif

#include <format>

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

    using namespace Media;

    ThemeChangeAlertBorder().Background(
        SolidColorBrush(Theme::get(Theme::Color::AlertBackground)));

    ThemeChangeAlertIcon().Foreground(
        SolidColorBrush(Theme::get(Theme::Color::AlertForeground)));
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

    ThemeChangeAlertBorder().Visibility(selected == AppSettings::CurrentTheme
                                            ? Visibility::Collapsed
                                            : Visibility::Visible);
}
void Settings::OpenTempFolder_Click(IInspectable const&,
                                    RoutedEventArgs const&) {
    auto folder =
        Windows::Storage::ApplicationData::Current().TemporaryFolder();
    Windows::System::Launcher::LaunchFolderAsync(folder);
}

fire_and_forget Settings::RickRollSwitch_Toggled(IInspectable const&,
                                              ToggleSwitch const& e) {
    auto dirtyHackIfYouCanFixThisSendMePullRequest = e;
    if (dirtyHackIfYouCanFixThisSendMePullRequest.IsOn())
        co_await Windows::System::Launcher::LaunchUriAsync(
            Uri(AppConstants::URLToHeaven));

    dirtyHackIfYouCanFixThisSendMePullRequest.IsOn(false);
}

}  // namespace winrt::RTX_2090_TiFy::implementation
