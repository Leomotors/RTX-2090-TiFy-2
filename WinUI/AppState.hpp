#pragma once

#include "GPUConfig.hpp"
#include "ImageHandler.hpp"

#include <optional>
#include <string>

namespace winrt::RTX_2090_TiFy {

class AppState {
  public:
    AppState() = delete;
    static RTXLib::ImageHandler ImageHandler;
    static RTXLib::GPUConfig GPUConfig;
    static bool IsLightTheme();
    /// <summary>
    /// Check if the app is ready to generate the video
    /// </summary>
    /// <returns>
    /// Reason for being Not RTX Ready, std::nullopt if is ready
    /// </returns>
    static std::optional<std::string> validate();
};

}  // namespace winrt::RTX_2090_TiFy
