#pragma once

#include "GPUConfig.hpp"
#include "ImageHandler.hpp"
#include "Macros/opencv.hpp"

#include <utility>
#include <vector>

namespace RTXLib {

class RayTracing {
  public:
    cv::Mat image;
    cv::Mat imageGray;
    cv::Mat imageHSV;
    cv::Scalar hsvMean;
    double imageGrayBrightness;
    const GPUConfig& config;

    cv::VideoWriter outVideo;

    RayTracing(const cv::Mat& inputImage, const GPUConfig& gpuConfig);
    std::pair<int, int> NextFrame();

  private:
    int totalFrame;
    int frameRendered = 0;
};

}  // namespace RTXLib
