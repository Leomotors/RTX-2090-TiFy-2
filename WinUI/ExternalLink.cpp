#include "pch.h"
#include "ExternalLink.h"
#if __has_include("ExternalLink.g.cpp")
#include "ExternalLink.g.cpp"
#endif

#include "AppState.hpp"

using namespace winrt;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;

namespace winrt::RTX_2090_TiFy::implementation {

ExternalLink::ExternalLink() {
    InitializeComponent();
}

//--- PROPERTY Text ---//

hstring ExternalLink::Text() { return GetValue(TextProperty).as<hstring>(); }

void ExternalLink::Text(hstring const &value) {
    SetValue(TextProperty, box_value(value));
}

DependencyProperty ExternalLink::TextProperty = DependencyProperty::Register(
    L"Text", xaml_typename<hstring>(),
    xaml_typename<RTX_2090_TiFy::ExternalLink>(), PropertyMetadata(nullptr));

hstring ExternalLink::Url() { return GetValue(UrlProperty).as<hstring>(); }

//--- PROPERTY URL ---//

void ExternalLink::Url(hstring const &value) {
    SetValue(UrlProperty, box_value(value));
}

DependencyProperty ExternalLink::UrlProperty = DependencyProperty::Register(
    L"Url", xaml_typename<hstring>(),
    xaml_typename<RTX_2090_TiFy::ExternalLink>(), PropertyMetadata(nullptr));

}  // namespace winrt::RTX_2090_TiFy::implementation
