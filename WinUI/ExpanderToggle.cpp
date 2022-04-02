#include "pch.h"
#include "ExpanderToggle.h"
#if __has_include("ExpanderToggle.g.cpp")
#include "ExpanderToggle.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::RTX_2090_TiFy::implementation {

ExpanderToggle::ExpanderToggle() { InitializeComponent(); }

//--- PROPERTY Glyph ---//

hstring ExpanderToggle::Glyph() {
    return GetValue(GlyphProperty).as<hstring>();
}

void ExpanderToggle::Glyph(hstring const &value) {
    SetValue(GlyphProperty, box_value(value));
}

DependencyProperty ExpanderToggle::GlyphProperty = DependencyProperty::Register(
    L"Glyph", winrt::xaml_typename<hstring>(),
    winrt::xaml_typename<RTX_2090_TiFy::ExpanderToggle>(),
    PropertyMetadata(nullptr));

//--- PROPERTY Text ---//

hstring ExpanderToggle::Text() { return GetValue(TextProperty).as<hstring>(); }

void ExpanderToggle::Text(hstring const &value) {
    SetValue(TextProperty, box_value(value));
}

DependencyProperty ExpanderToggle::TextProperty = DependencyProperty::Register(
    L"Text", xaml_typename<hstring>(),
    xaml_typename<RTX_2090_TiFy::ExpanderToggle>(), PropertyMetadata(nullptr));

//--- EVENT Switch_Toggled ---//

event_token ExpanderToggle::Switch_Toggled(
    EventHandler<ToggleSwitch> const &handler) {
    return m_Switch_Toggled.add(handler);
}

void ExpanderToggle::Switch_Toggled(event_token const &token) {
    m_Switch_Toggled.remove(token);
}

void ExpanderToggle::ToggleSwitch_Toggled(IInspectable const &sender,
                                          RoutedEventArgs const &) {
    m_Switch_Toggled(*this, sender.as<ToggleSwitch>());
}

}  // namespace winrt::RTX_2090_TiFy::implementation
