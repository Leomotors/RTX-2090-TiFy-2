#include "pch.h"

#include "MainPage.h"
#include "MainPage.g.cpp"

using namespace winrt;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::ViewManagement;
using namespace Windows::ApplicationModel::Core;

namespace winrt::RTX_2090_TiFy::implementation {

MainPage::MainPage() {
    InitializeComponent();

    auto titleBar = ApplicationView::GetForCurrentView().TitleBar();
    titleBar.ButtonBackgroundColor(Colors::Transparent());

    titleBar.ButtonInactiveBackgroundColor(Colors::Transparent());

    // Hide Default Title Bar
    auto coreTitleBar = CoreApplication::GetCurrentView().TitleBar();
    coreTitleBar.ExtendViewIntoTitleBar(true);

    // Set XAML element as a draggable region
    Window::Current().SetTitleBar(AppTitleBar());

#ifdef _DEBUG
    AppTitle().Text(AppTitle().Text() + L" (DEBUG Edition)");
#endif
}

int32_t MainPage::MyProperty() { throw hresult_not_implemented(); }

void MainPage::MyProperty(int32_t) {
    throw hresult_not_implemented();
}

}  // namespace winrt::RTX_2090_TiFy::implementation
