#pragma once

#include "Macros/opencv.hpp"

#include <string>
#include <utility>

namespace RTXLib {

/// <summary>
/// Handle Input Image and process it before shipping to RTX Factory
/// </summary>
class ImageHandler {
  public:
    std::string path;
    cv::Mat image;
    std::pair<int, int> dims;

    bool status = false;

    bool loadImage(const std::string& filePath);
    bool ready() const;
};

}  // namespace RTXLib
