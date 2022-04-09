#pragma once

#include "GPUConfig.hpp"
#include "ImageHandler.hpp"
#include "Macros/opencv.hpp"

#include <utility>
#include <vector>

namespace RTXLib {

/**
 * Class that is responsible for generating frames based on configurations.
 */
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
    ~RayTracing();
    std::pair<int, int> NextFrame();
    cv::Mat buildFrame();

    inline int getTotalFrame() const { return m_totalFrame; }

  private:
    int m_totalFrame;
    int m_frameRendered = 0;
};

}  // namespace RTXLib
