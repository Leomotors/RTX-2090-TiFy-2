#pragma once

#include "HomePage.g.h"

#include <map>
#include "GPUConfig.hpp"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;

namespace winrt::RTX_2090_TiFy::implementation {

struct HomePage : HomePageT<HomePage> {
    HomePage();

    std::map<hstring,RTXLib::Algorithm> hstringToAlgorithm;

    fire_and_forget SelectInput_Click(IInspectable const& sender,
                                      RoutedEventArgs const& e);
};

}  // namespace winrt::RTX_2090_TiFy::implementation

namespace winrt::RTX_2090_TiFy::factory_implementation {
struct HomePage : HomePageT<HomePage, implementation::HomePage> {};
}  // namespace winrt::RTX_2090_TiFy::factory_implementation
