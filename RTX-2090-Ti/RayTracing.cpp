#include "pch.h"

#include "RayTracing.hpp"

namespace RTXLib {

RayTracing::RayTracing(const cv::Mat& inputImage, const GPUConfig& gpuConfig)
    : config(gpuConfig) {
    // Preprocess Images
    image = inputImage.clone();
    cv::cvtColor(inputImage, imageGray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(inputImage, imageHSV, cv::COLOR_BGR2HSV);

    // Prepare output Video Writer
    const auto [x, y] = config.output.dims;

    outVideo.open(config.output.path + ".avi",
                  cv::VideoWriter::fourcc('X', 'V', 'I', 'D'),
                  config.output.fps, {x, y});

    outVideo.write(image);

    // Preprocess HSV Data
    std::vector<cv::Mat> HSVChannels;
    cv::split(imageHSV, HSVChannels);

    // Preprocess Gray Image Data
    double totalBrightness = 0;
    for (int r = 0; r < imageGray.rows; r++) {
        for (int c = 0; c < imageGray.cols; c++) {
            totalBrightness += imageGray.at<uint8_t>(r, c);
        }
    }
    imageGrayBrightness =
        totalBrightness /
        (static_cast<double>(imageGray.rows) * imageGray.cols * 255);

    // Preprocess misc data
    m_totalFrame =
        static_cast<int32_t>(config.output.fps * config.output.length) *
        config.output.loops;
}

RayTracing::~RayTracing() { outVideo.release(); }

std::pair<int, int> RayTracing::NextFrame() {
    m_frameRendered++;
    // todo IMPLEMENT
    cv::Mat temp;
    cv::resize(m_frameRendered % 2 ? image : imageGray, temp,
               {config.output.dims.first, config.output.dims.second});
    outVideo.write(temp);
    return {m_frameRendered, m_totalFrame};
}

}  // namespace RTXLib
