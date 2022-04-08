#include "pch.h"
#include "ImageHandler.hpp"

#include <string>
#include <Macros/opencv.hpp>

namespace RTXLib {

bool ImageHandler::loadImage(const std::string& filePath) {
    cv::Mat inImg = cv::imread(filePath);
    if (inImg.empty()) return false;

    path = filePath;
    image = inImg;
    dims = {image.rows, image.cols};
    return true;
}

bool ImageHandler::ready() const { return !image.empty(); }

}  // namespace RTXLib
