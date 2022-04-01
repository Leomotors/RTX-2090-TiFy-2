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

    EventHandler<ToggleSwitch> Switch_Toggled();
    void Switch_Toggled(EventHandler<ToggleSwitch> const& value);
    static DependencyProperty Switch_ToggledProperty;

    void ToggleSwitch_Toggled(IInspectable const& sender,
                              RoutedEventArgs const& e);
};

}  // namespace winrt::RTX_2090_TiFy::implementation

namespace winrt::RTX_2090_TiFy::factory_implementation {
struct ExpanderToggle
    : ExpanderToggleT<ExpanderToggle, implementation::ExpanderToggle> {};
}  // namespace winrt::RTX_2090_TiFy::factory_implementation
