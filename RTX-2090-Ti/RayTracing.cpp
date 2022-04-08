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

    outVideo = cv::VideoWriter(config.output.path,
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
    totalFrame = config.output.fps * config.output.length * config.output.loops;
}

std::pair<int, int> RayTracing::NextFrame() {
    frameRendered++;
    return {frameRendered, totalFrame};
}

}  // namespace RTXLib
