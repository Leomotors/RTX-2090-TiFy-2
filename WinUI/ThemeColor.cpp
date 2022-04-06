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
// };

Windows::UI::Color get(Color key) {
    if (!IsInitialized) {
        IsInitialized = true;
        bool IsLight = AppState::IsLightTheme();
        using WinColor = Windows::UI::Color;
        // Theme Colors are color picked from system apps' UI
        // to achieve most window-ish experience
        // Copied from You are a Failure!
        Colors = {
            IsLight ? WinColor(255, 0, 62, 146) : WinColor(255, 153, 235, 255),
        };
    }

    return Colors.at(static_cast<int32_t>(key));
}

}  // namespace winrt::RTX_2090_TiFy::Theme
