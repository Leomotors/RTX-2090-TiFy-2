#pragma once

#include "ExternalLink.g.h"

namespace winrt::RTX_2090_TiFy::implementation {

struct ExternalLink : ExternalLinkT<ExternalLink> {
    ExternalLink();

    static Windows::UI::Color ExtLinkColor;

    hstring Text();
    void Text(hstring const& value);
    static DependencyProperty TextProperty;

    hstring Url();
    void Url(hstring const& value);
    static DependencyProperty UrlProperty;
};

}  // namespace winrt::RTX_2090_TiFy::implementation

namespace winrt::RTX_2090_TiFy::factory_implementation {
struct ExternalLink
    : ExternalLinkT<ExternalLink, implementation::ExternalLink> {};
}  // namespace winrt::RTX_2090_TiFy::factory_implementation
