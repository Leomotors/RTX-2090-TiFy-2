#pragma once

#include <opencv2/opencv.hpp>
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
    cv::Mat imageGray;
    std::pair<int, int> dims;

    bool status = false;

    bool loadImage(std::string filePath);
};

}  // namespace RTXLib
