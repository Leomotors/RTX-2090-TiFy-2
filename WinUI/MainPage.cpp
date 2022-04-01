#include "pch.h"

#include "MainPage.h"
#include "MainPage.g.cpp"

#include "AppState.hpp"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::ViewManagement;
using namespace Windows::ApplicationModel::Core;

namespace winrt::RTX_2090_TiFy::implementation {

MainPage::MainPage() {
    InitializeComponent();

    auto titleBar = ApplicationView::GetForCurrentView().TitleBar();

    titleBar.ButtonBackgroundColor(Colors::Transparent());
    titleBar.ButtonInactiveBackgroundColor(Colors::Transparent());

    if (AppState::IsLightTheme()) {
        titleBar.ButtonForegroundColor(Colors::Black());
        titleBar.ButtonHoverForegroundColor(Colors::Black());
        titleBar.ButtonPressedForegroundColor(Colors::Black());

        titleBar.ButtonHoverBackgroundColor(Color(32, 0, 0, 0));
        titleBar.ButtonPressedBackgroundColor(Color(16, 0, 0, 0));
    } else {
        titleBar.ButtonForegroundColor(Colors::White());
        titleBar.ButtonHoverForegroundColor(Colors::White());
        titleBar.ButtonPressedForegroundColor(Colors::White());

        titleBar.ButtonHoverBackgroundColor(Color(32, 255, 255, 255));
        titleBar.ButtonPressedBackgroundColor(Color(16, 255, 255, 255));
    }

    // Hide Default Title Bar
    auto coreTitleBar = CoreApplication::GetCurrentView().TitleBar();
    coreTitleBar.ExtendViewIntoTitleBar(true);

    // Set XAML element as a draggable region
    Window::Current().SetTitleBar(AppTitleBar());

#ifdef _DEBUG
    AppTitle().Text(AppTitle().Text() + L" (DEBUG Edition)");
#endif
}

void MainPage::Settings_Click(IInspectable const&, RoutedEventArgs const&) {
    ContentFrame().Navigate(xaml_typename<Settings>());
}

void MainPage::NavigationView_SelectionChanged(
    Microsoft::UI::Xaml::Controls::NavigationView const& sender,
    Microsoft::UI::Xaml::Controls::
        NavigationViewSelectionChangedEventArgs const& args) {
    auto nav = sender.as<Microsoft::UI::Xaml::Controls::NavigationView>();
    nav.IsBackEnabled(true);

    if (args.IsSettingsSelected()) {
        ContentFrame().Navigate(xaml_typename<Settings>());
        return;
    }

    ContentFrame().Navigate(xaml_typename<HomePage>());
    nav.IsBackEnabled(ContentFrame().CanGoBack());
}

}  // namespace winrt::RTX_2090_TiFy::implementation
