#pragma once

#include "MainPage.g.h"

namespace winrt::RTX_2090_TiFy::implementation {
struct MainPage : MainPageT<MainPage> {
    MainPage();

    int32_t MyProperty();
    void MyProperty(int32_t value);
};
}  // namespace winrt::RTX_2090_TiFy::implementation

namespace winrt::RTX_2090_TiFy::factory_implementation {
struct MainPage : MainPageT<MainPage, implementation::MainPage> {};
}  // namespace winrt::RTX_2090_TiFy::factory_implementation
