#pragma once

#include "MainPage.g.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;

namespace winrt::RTX_2090_TiFy::implementation {

struct MainPage : MainPageT<MainPage> {
    MainPage();

    void Settings_Click(IInspectable const& sender, RoutedEventArgs const& e);
    void NavigationView_SelectionChanged(
        Microsoft::UI::Xaml::Controls::NavigationView const& sender,
        Microsoft::UI::Xaml::Controls::
            NavigationViewSelectionChangedEventArgs const& args);
};

}  // namespace winrt::RTX_2090_TiFy::implementation

namespace winrt::RTX_2090_TiFy::factory_implementation {
struct MainPage : MainPageT<MainPage, implementation::MainPage> {};
}  // namespace winrt::RTX_2090_TiFy::factory_implementation
