#include "pch.h"
#include "ImageHandler.hpp"

#include <string>
#include <Macros/opencv.hpp>

namespace RTXLib {

bool ImageHandler::loadImage(std::string filePath) {
    cv::Mat inImg = cv::imread(filePath);
    if (inImg.empty()) return false;

    path = filePath;
    image = inImg;
    cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);
    dims = {image.rows, image.cols};
    return true;
}

}  // namespace RTXLib
