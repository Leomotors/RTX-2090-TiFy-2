#include "pch.h"
#include "GPUConfig.hpp"

#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <random>

namespace RTXLib {

bool GPUConfig::setOutputDims(std::pair<int, int> newDims) {
    output.dims = newDims;

    return validateWarpLocations();
}

bool GPUConfig::setWarpLocations(std::string locations) {
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

bool GPUConfig::setWarpLocations(std::vector<std::pair<int, int>> locations) {
    warpLocations = locations;
    return validateWarpLocations();
}

bool GPUConfig::validateWarpLocations() {
    std::vector<std::pair<int, int>> passedValidation;

    bool changed = false;
    bool changed2 = output.loops != warpLocations.size();

    for (const auto &[x, y] : warpLocations) {
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
    std::uniform_int_distribution<int> distribX(0, output.dims.first);
    std::uniform_int_distribution<int> distribY(0, output.dims.second);

    while (passedValidation.size() < output.loops) {
        passedValidation.push_back({distribX(gen), distribY(gen)});
    }

    warpLocations = std::move(passedValidation);

    return changed || changed2;
}

}  // namespace RTXLib
