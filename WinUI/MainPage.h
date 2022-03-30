#pragma once

#include "MainPage.g.h"

namespace winrt::RTX_2090_TiFy::implementation {
struct MainPage : MainPageT<MainPage> {
    MainPage();

    int32_t MyProperty();
    void MyProperty(int32_t value);
    Windows::Foundation::IAsyncAction SelectInput_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    Windows::Foundation::IAsyncAction SelectOutput_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    Windows::Foundation::IAsyncAction License_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    Windows::Foundation::IAsyncAction VisitSite_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    Windows::Foundation::IAsyncAction About_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
};
}  // namespace winrt::RTX_2090_TiFy::implementation

namespace winrt::RTX_2090_TiFy::factory_implementation {
struct MainPage : MainPageT<MainPage, implementation::MainPage> {};
}  // namespace winrt::RTX_2090_TiFy::factory_implementation
