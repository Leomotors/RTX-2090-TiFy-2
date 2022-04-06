#include "pch.h"
#include "AppState.hpp"

#include <optional>

namespace winrt::RTX_2090_TiFy {

RTXLib::ImageHandler AppState::ImageHandler;
RTXLib::GPUConfig AppState::GPUConfig;

bool AppState::IsLightTheme() {
    using namespace Windows::UI::Xaml;
    return Application::Current().RequestedTheme() == ApplicationTheme::Light;
}

std::optional<std::string> AppState::validate() {
    if (!ImageHandler.ready()) return "Input Image is not ready";

    auto outputFail = GPUConfig.output.validate();
    if (outputFail.has_value()) return outputFail;

    if (GPUConfig.validateWarpLocations()) {
        return "Warp locations are not valid, "
               "YOU SHOULD NOT SEE THIS ERROR MESSAGE!";
    }

    return std::nullopt;
}

}  // namespace winrt::RTX_2090_TiFy
