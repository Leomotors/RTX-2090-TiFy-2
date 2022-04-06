#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "ImageHandler.hpp"

namespace RTXLib {

enum class Algorithm {
    CORGI_LEGACY = 69,
    BRIGHTNESS_COMPENSATE = 420,
    CORGI_HSV = 1337,
    BLEND_S = 177013
};

const auto ConfigLists = std::vector<std::string>{
    "Output Video Path", "Output Video Resolution",
    "Output Video FPS",  "Output Video Length Per Loop",
    "Number of Loops",   "Algorithm"};

const auto ConfigDescription = std::vector<std::string>{
    "The path to the output video file.",
    "The resolution of the output video file.",
    "The FPS of the output video file.",
    "The length of each loop in the output video file.",
    "The number of loops to be made in the output video file.",
    "The algorithm to be used in rendering."};

const auto AlgoEnumToString = std::map<Algorithm, std::string>{
    {Algorithm::CORGI_LEGACY, "Corgi Legacy"},
    {Algorithm::BRIGHTNESS_COMPENSATE,
     "Corgi Legacy with Brightness Compensate"},
    {Algorithm::CORGI_HSV, "Corgi HIV"},
    {Algorithm::BLEND_S, "Blend Sukhoi"}};

const auto OutputConfigConstraint = std::vector<std::string>{
    "Path must not be empty!", "Dimension must ...", "FPS must be at least 1",
    "Length must be at least 1 seconds", "Number of loops must be at least 1"};

struct OutputConfig {
    // Ordered according to ConfigLists & ConfigDescription
    std::string path;
    std::pair<int, int> dims = {480, 480};
    int fps = 30;
    double length = 5.5;
    int loops = 6;
    Algorithm algo = Algorithm::BLEND_S;
};

/// <summary>
/// Configuration payload for generating video,
/// does not relate to GPU like its name.

/// reminder: everything here is meme.
/// </summary>
class GPUConfig {
  public:
    GPUConfig();
    std::string inputPath;
    OutputConfig output;
    std::vector<std::pair<int, int>> warpLocations;

    bool setOutputDims(std::pair<int, int> newDims);

    bool setWarpLocations(std::string locations);
    bool setWarpLocations(std::vector<std::pair<int, int>> locations);
    /// <summary>
    /// Remove Invalid Warp Locations based on current dims,
    /// automatically added missing warp locations
    /// </summary>
    /// <returns>true if warp locations is changed</returns>
    bool validateWarpLocations();
    void resetWarpLocations();
    std::string warpLocationsAsStr();
};

}  // namespace RTXLib
