#pragma once

#include <vector>

namespace winrt::RTX_2090_TiFy::Theme {

extern bool IsInitialized;
extern std::vector<Windows::UI::Color> Colors;

enum class Color {
    ExternalLink = 0,
};

Windows::UI::Color get(Color key);

}  // namespace winrt::RTX_2090_TiFy::Theme
