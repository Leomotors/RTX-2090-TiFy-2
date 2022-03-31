#pragma once

#include "ImageHandler.hpp"

namespace winrt::RTX_2090_TiFy {

class AppState {
  public:
    static RTXLib::ImageHandler ImageHandler;
    static bool IsLightTheme();
};

}  // namespace winrt::RTX_2090_TiFy
