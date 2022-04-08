#include "pch.h"
#include "GPUConfig.hpp"

#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <random>
#include <optional>

namespace RTXLib {

std::optional<std::string> OutputConfig::validate() const {
    if (path.empty())
#ifdef _MSC_VER
        return "Output Path is empty, but UWP Version App will take care of "
               "the output Path, YOU SHOULD NOT SEE THIS MESSAGE!";
#else
        return "Output Path is empty";
#endif

    if (dims.first < 144 || dims.second < 144)
        return "Dimensions must be at least 144x144";

    if (fps < 5) return "FPS must be at least 5";

    if (length < 0.5) return "Length per loop must be at least 0.5 seconds";

    if (loops < 1)
        return "Number of loops less than 1 cannot make the video exist!";

    return std::nullopt;
}

GPUConfig::GPUConfig() { resetWarpLocations(); }

bool GPUConfig::setOutputDims(const std::pair<int, int>& newDims) {
    output.dims = newDims;

    return validateWarpLocations();
}

bool GPUConfig::setWarpLocations(const std::string& locations) {
    std::stringstream ss(locations);

    std::string token;

    std::vector<std::pair<int, int>> parsedLocs;

    while (ss >> token) {
        int x, y;
        sscanf_s(token.c_str(), "%dx%d", &x, &y);
        parsedLocs.push_back({x, y});
    }

    return setWarpLocations(parsedLocs);
}

bool GPUConfig::setWarpLocations(
    const std::vector<std::pair<int, int>>& locations) {
    warpLocations = locations;
    return validateWarpLocations();
}

bool GPUConfig::validateWarpLocations() {
    std::vector<std::pair<int, int>> passedValidation;

    bool changed = false;
    bool changed2 = output.loops != warpLocations.size();

    for (const auto& [x, y] : warpLocations) {
        if (x >= 0 && x < output.dims.first && y >= 0 &&
            y < output.dims.second) {
            passedValidation.push_back({x, y});
        } else {
            changed = true;
        }

        if (passedValidation.size() >= output.loops) break;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribX(0, output.dims.first - 1);
    std::uniform_int_distribution<int> distribY(0, output.dims.second - 1);

    while (passedValidation.size() < output.loops) {
        passedValidation.push_back({distribX(gen), distribY(gen)});
    }

    warpLocations = std::move(passedValidation);

    return changed || changed2;
}

void GPUConfig::resetWarpLocations() {
    warpLocations.clear();
    validateWarpLocations();
}

std::string GPUConfig::warpLocationsAsStr() const {
    std::string res = "";

    for (const auto& [x, y] : warpLocations) {
        res += std::to_string(x) + 'x' + std::to_string(y) + '\n';
    }

    if (!res.empty()) res.pop_back();

    return res;
}

}  // namespace RTXLib
