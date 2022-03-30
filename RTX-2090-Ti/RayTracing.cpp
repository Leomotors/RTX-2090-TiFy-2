#include "./RayTracing.hpp"

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <tuple>
#include <utility>

#include "Configurations.hpp"
#include "CorgiAlgorithm.hpp"
#include "IProgressBar.hpp"
#include "Video.hpp"

constexpr auto SMOL_IMG_PAUSE = 0.18;
constexpr auto BLEND_START = 0.09;
constexpr auto EXPANSION_GROWTH = 2.77;

RTX2090Ti::RTX2090Ti(IProgressBar &progressBar, cv::Mat BaseImage,
                     Configurations &Config)
    : progressBar(progressBar),
      Config(Config),
      fourcc(cv::VideoWriter::fourcc(MYCODEC)) {
    const auto &[x, y] = Config.Resolution;
    cols = x;
    rows = y;

    cv::resize(BaseImage, this->BaseImage, cv::Size(x, y));
    cv::cvtColor(this->BaseImage, BaseImageGray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(this->BaseImage, BaseImageHSV, cv::COLOR_BGR2HSV);

    OutVideo = cv::VideoWriter(Config.OutVideoPath + ".avi", fourcc, Config.FPS,
                               cv::Size(cols, rows));
    OutVideo.write(this->BaseImage);

    std::vector<cv::Mat> HSVChannels;
    cv::split(BaseImageHSV, HSVChannels);
    HSVMean = cv::mean(HSVChannels[2]);

    double totalBrightness{0};
    for (int r = 0; r < BaseImageGray.rows; r++) {
        for (int c = 0; c < BaseImageGray.cols; c++) {
            totalBrightness += BaseImageGray.at<u_char>(r, c);
        }
    }
    ImageGrayBrightness =
        totalBrightness / (BaseImageGray.rows * BaseImageGray.cols * 255);
}

bool RTX2090Ti::buildVideo() {
    auto start{std::chrono::steady_clock::now()};

    int totalFrames = Config.FPS * Config.LoopDuration;

    progressBar.InitDialog(statusMessage(0, Config.nLoops, 0, totalFrames),
                           totalFrames * Config.nLoops);

    // wxProgressDialog BuildProgress(
    //     "Building Video...", statusMessage(0, Config.nLoops, 0, totalFrames),
    //     totalFrames * Config.nLoops, parent);

    std::cout << "Building Video with these properties\n"
              << "Resolution: " << cols << "x" << rows << "\n"
              << "FPS: " << Config.FPS << "\n"
              << "Duration Per Loop: " << Config.LoopDuration << "\n"
              << "Number of Loops: " << Config.nLoops << "\n"
              << "Saving as: " << Config.OutVideoPath << "\n"
              << "Total of: " << totalFrames * Config.nLoops << " frames\n"
              << "Using Algorithm: "
              << Config.Algorithms[Config.chosenAlgorithm] << "\n";

    int loopDone{0};
    cv::Mat temp(cv::Mat::zeros(cols, rows, CV_8UC3));

    for (std::pair<int, int> &point : Config.WarpPosition) {
        int framesDone = loopDone * totalFrames;

        std::pair<int, int> Start{point.first * cols, point.second * rows};
        std::pair<int, int> End{(point.first + 1) * cols,
                                (point.second + 1) * rows + 1};

        int left = cols * point.first;
        int up = rows * point.second;
        int right = cols * (cols - point.first - 1);
        int down = rows * (rows - point.second - 1);

        for (int f = 1; f <= totalFrames; f++) {
            double expansionRate = (double)f / totalFrames;
            expansionRate = std::pow(expansionRate, EXPANSION_GROWTH);

            std::pair<int, int> LocalStart{
                Start.first - std::round(left * expansionRate),
                Start.second - std::round(up * expansionRate)};
            std::pair<int, int> LocalEnd{
                End.first + std::round(right * expansionRate),
                End.second + std::round(down * expansionRate)};

            RayTracing(OutVideo, LocalStart, LocalEnd, point);

            // BuildProgress.Update(
            //     framesDone + f,
            //     statusMessage(loopDone, Config.nLoops, f, totalFrames));

            progressBar.UpdateDialog(
                statusMessage(loopDone, Config.nLoops, f, totalFrames),
                framesDone + f);
        }

        loopDone++;
    }

    cv::destroyAllWindows();
    OutVideo.release();
    std::cout << "Video Build Success\n";

    Video::linkAudio(Config.OutVideoPath, Config.LoopDuration * Config.nLoops);

    auto end{std::chrono::steady_clock::now()};

    std::chrono::duration<double> time_took = end - start;
    std::cout << "Building Video took " << time_took.count() << " secs.\n";

    // wxMessageDialog doneMessage(
    //     parent,
    //     "Build Success! Took " + std::to_string(time_took.count()) +
    //         " seconds.\nYour Video is Ready, would you like to open the
    //         video?"
    //         "\nIMPORTANT: FFmpeg must be included in your path, otherwise "
    //         "video will not appear",
    //     "Build Success", wxOK | wxCANCEL);

    // if (doneMessage.ShowModal() == wxID_OK) {
    //     wxLaunchDefaultApplication(Config.OutVideoPath + ".mp4");
    // }

    return true;
}

void RTX2090Ti::RayTracing(cv::VideoWriter &OutVideo,
                           std::pair<int, int> &Start, std::pair<int, int> &End,
                           std::pair<int, int> &OriginalLoc) {
    double pixelSizeFactor = (double)(End.first - Start.first) / (cols * cols);

    if (pixelSizeFactor >= SMOL_IMG_PAUSE) {
        cv::Mat cropped_img =
            BaseImage(cv::Range(std::round(Start.second / (double)rows),
                                std::round(End.second / (double)rows)),
                      cv::Range(std::round(Start.first / (double)cols),
                                std::round(End.first / (double)cols)));

        cv::resize(cropped_img, cropped_img, cv::Size(cols, rows));
        OutVideo.write(cropped_img);

        cv::imshow("Live Preview", cropped_img);
        return;
    }

    cv::Mat Canvas = cv::Mat::zeros(cv::Size(cols, rows), CV_8UC3);

    std::pair<int, int> Imsize{End.first - Start.first,
                               End.second - Start.second};

    std::pair<int, int> BigTileStart{Start.first / cols, Start.second / rows};
    std::pair<int, int> BigTileEnd{std::ceil((double)End.first / cols),
                                   std::ceil((double)End.second / rows)};

    std::pair<int, int> PixelSize{
        std::round((double)cols * cols / Imsize.first) + 1,
        std::round((double)rows * rows / Imsize.second) + 1};

    cv::Mat SmolImage;
    if (Config.chosenAlgorithm == CORGI_HSV)
        cv::resize(BaseImageHSV, SmolImage,
                   cv::Size(PixelSize.first, PixelSize.second));
    else
        cv::resize(BaseImageGray, SmolImage,
                   cv::Size(PixelSize.first, PixelSize.second));

    for (int c = BigTileStart.first; c < BigTileEnd.first; c++) {
        for (int r = BigTileStart.second; r < BigTileEnd.second; r++) {
            renderPixel(c, r, Start, End, SmolImage, Canvas, OriginalLoc);
        }
    }

    if (Config.chosenAlgorithm == BLEND_S && pixelSizeFactor >= BLEND_START) {
        double blendFactor =
            (pixelSizeFactor - BLEND_START) / (SMOL_IMG_PAUSE - BLEND_START);
        cv::Mat cropped_img =
            BaseImage(cv::Range(std::round(Start.second / (double)rows),
                                std::round(End.second / (double)rows)),
                      cv::Range(std::round(Start.first / (double)cols),
                                std::round(End.first / (double)cols)));

        cv::resize(cropped_img, cropped_img, cv::Size(cols, rows));

        Canvas *= (1 - blendFactor);
        Canvas += (cropped_img * blendFactor);
    }

    OutVideo.write(Canvas);
    cv::imshow("Live Preview", Canvas);
}

void RTX2090Ti::renderPixel(int c, int r, std::pair<int, int> &Start,
                            std::pair<int, int> &End, cv::Mat &normalizedPic,
                            cv::Mat &RenderOn,
                            std::pair<int, int> &OriginalLoc) {
    cv::Mat ColoredImg;

    if (Config.chosenAlgorithm == CORGI_LEGACY ||
        Config.chosenAlgorithm == BLEND_S) {
        cv::Vec3b color = BaseImage.at<cv::Vec3b>(cv::Point(c, r));
        ColoredImg = Corgi::changeTone(
            normalizedPic,
            std::tuple<int, int, int>(color[0], color[1], color[2]));
    } else if (Config.chosenAlgorithm == BRIGHTNESS_COMPENSATE) {
        cv::Vec3b color = BaseImage.at<cv::Vec3b>(cv::Point(c, r));
        ColoredImg = Corgi::changeTone(
            normalizedPic,
            std::tuple<int, int, int>(color[0], color[1], color[2]),
            ImageGrayBrightness);
    } else if (Config.chosenAlgorithm == CORGI_HSV) {
        cv::Vec3b color = BaseImageHSV.at<cv::Vec3b>(cv::Point(c, r));
        ColoredImg = Corgi::changeTone_HSV(
            normalizedPic,
            std::tuple<int, int, int>(color[0], color[1], color[2]));
    } else {
        throw "Some Function is SUS";
    }

    cv::Point renderOnPos(
        (c * cols - Start.first) * cols / (End.first - Start.first),
        (r * rows - Start.second) * rows / (End.second - Start.second));

    cv::Point renderEnd(renderOnPos.x + normalizedPic.cols,
                        renderOnPos.y + normalizedPic.rows);

    cv::Rect renderRange(renderOnPos, renderEnd);

    // * Case: Original Picture
    if (c == OriginalLoc.first && r == OriginalLoc.second) {
        cv::Mat toRender;
        cv::resize(BaseImage, toRender,
                   cv::Size(normalizedPic.cols, normalizedPic.rows));

        safeCopyTo(toRender, RenderOn, renderRange);

        return;
    }

    // * General Case
    safeCopyTo(ColoredImg, RenderOn, renderRange);
}

void RTX2090Ti::safeCopyTo(cv::Mat &src, cv::Mat &dest, cv::Rect &roi) {
    std::pair<int, int> newXRange{0, roi.width};
    std::pair<int, int> newYRange{0, roi.height};

    bool left{false};
    bool up{false};
    bool right{false};
    bool down{false};

    if (roi.x < 0) {
        newXRange.first = -roi.x;
        left = true;
    }
    if (roi.y < 0) {
        newYRange.first = -roi.y;
        up = true;
    }
    if (roi.x + roi.width > cols) {
        newXRange.second = cols - roi.x;
        right = true;
    }
    if (roi.y + roi.height > rows) {
        newYRange.second = rows - roi.y;
        down = true;
    }

    if (left || up || right || down) {
        src = src(cv::Range(newYRange.first, newYRange.second),
                  cv::Range(newXRange.first, newXRange.second));

        if (left) {
            roi.width += roi.x;
            roi.x = 0;
        }
        if (right) {
            roi.width = src.cols;
        }
        if (up) {
            roi.height += roi.y;
            roi.y = 0;
        }
        if (down) {
            roi.height = src.rows;
        }
    }

    src.copyTo(dest(roi));
}

std::string RTX2090Ti::statusMessage(int loopsDone, int allLoops,
                                     int framesDone, int allFrames) {
    std::string result;
    result += "Loops Done: " + std::to_string(loopsDone) + " of " +
              std::to_string(allLoops);
    result += "\n";
    result += "Frames Done: " + std::to_string(framesDone) + " of " +
              std::to_string(allFrames);
    return result;
}
