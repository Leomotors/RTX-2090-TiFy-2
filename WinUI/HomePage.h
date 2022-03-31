#pragma once

#include "HomePage.g.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;

namespace winrt::RTX_2090_TiFy::implementation {
struct HomePage : HomePageT<HomePage> {
    HomePage();

    IAsyncAction SelectInput_Click(IInspectable const& sender,
                                   RoutedEventArgs const& e);
};
}  // namespace winrt::RTX_2090_TiFy::implementation

namespace winrt::RTX_2090_TiFy::factory_implementation {
struct HomePage : HomePageT<HomePage, implementation::HomePage> {};
}  // namespace winrt::RTX_2090_TiFy::factory_implementation
