#pragma once

#include "Settings.g.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;

namespace winrt::RTX_2090_TiFy::implementation {

struct Settings : SettingsT<Settings> {
    Settings();

    IAsyncAction License_Click(IInspectable const& sender,
                               RoutedEventArgs const& e);
    IAsyncAction About_Click(IInspectable const& sender,
                             RoutedEventArgs const& e);
    void ThemeSelector_Loaded(IInspectable const& sender,
                              RoutedEventArgs const& e);
    void Theme_SelectionChanged(IInspectable const& sender,
                                Controls::SelectionChangedEventArgs const& e);
    void OpenTempFolder_Click(IInspectable const& sender,
                              RoutedEventArgs const& e);
    IAsyncAction RickRollSwitch_Toggled(IInspectable const& sender,
                                RoutedEventArgs const& e);
};

}  // namespace winrt::RTX_2090_TiFy::implementation

namespace winrt::RTX_2090_TiFy::factory_implementation {
struct Settings : SettingsT<Settings, implementation::Settings> {};
}  // namespace winrt::RTX_2090_TiFy::factory_implementation
