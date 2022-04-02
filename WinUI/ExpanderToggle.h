#pragma once

#include "ExpanderToggle.g.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::RTX_2090_TiFy::implementation {

struct ExpanderToggle : ExpanderToggleT<ExpanderToggle> {
    ExpanderToggle();

    hstring Glyph();
    void Glyph(hstring const& value);
    static DependencyProperty GlyphProperty;

    hstring Text();
    void Text(hstring const& value);
    static DependencyProperty TextProperty;

    event_token Switch_Toggled(EventHandler<ToggleSwitch> const& value);
    void Switch_Toggled(event_token const& token);
    event<EventHandler<ToggleSwitch>> m_Switch_Toggled;

    void ToggleSwitch_Toggled(IInspectable const& sender,
                              RoutedEventArgs const& e);
};

}  // namespace winrt::RTX_2090_TiFy::implementation

namespace winrt::RTX_2090_TiFy::factory_implementation {
struct ExpanderToggle
    : ExpanderToggleT<ExpanderToggle, implementation::ExpanderToggle> {};
}  // namespace winrt::RTX_2090_TiFy::factory_implementation
