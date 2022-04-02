#include "pch.h"
#include "ThemeColor.hpp"

#include "AppState.hpp"

#include <vector>

namespace winrt::RTX_2090_TiFy::Theme {

bool IsInitialized = false;
std::vector<Windows::UI::Color> Colors;

// For reference
// enum class Color {
//     ExternalLink = 0,
//     AlertForeground = 1,
//     AlertBackground = 2,
// };

Windows::UI::Color get(Color key) {
    if (!IsInitialized) {
        bool IsLight = AppState::IsLightTheme();
        using WinColor = Windows::UI::Color;
        // Theme Colors are color picked from System
        // Copied from You are a Failure!
        Colors = {
            IsLight ? WinColor(255, 0, 62, 146) : WinColor(255, 153, 235, 255),
            IsLight ? WinColor(255, 157, 93, 0) : WinColor(255, 252, 225, 0),
            IsLight ? WinColor(255, 255, 244, 206) : WinColor(255, 67, 53, 25)};
    }

    return Colors.at(static_cast<int32_t>(key));
}

}  // namespace winrt::RTX_2090_TiFy::Theme
