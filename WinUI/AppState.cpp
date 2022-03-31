#include "pch.h"
#include "AppState.hpp"

namespace winrt::RTX_2090_TiFy {

RTXLib::ImageHandler AppState::ImageHandler;

bool AppState::IsLightTheme() {
    using namespace Windows::UI::Xaml;
    return Application::Current().RequestedTheme() == ApplicationTheme::Light;
}

}  // namespace winrt::RTX_2090_TiFy
