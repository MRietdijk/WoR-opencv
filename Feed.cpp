#include "Feed.h"
#include <array>

// Custom HSV values
std::array<int, 6> orangeHSV = {0, 110, 148, 43, 242, 255};
std::array<int, 6> greenHSV = {50, 120, 100, 179, 255, 255};
std::array<int, 6> yellowHSV = {10, 0, 0, 60, 160, 255};
std::array<int, 6> pinkHSV = {150, 34, 70, 179, 255, 255};


Feed::Feed(std::string file) : ticks(clock())
{
}

void Feed::showFound(cv::Mat img, contoursType contours, bool printing /* = false*/) {
    for (uint8_t i = 0; i < contours.size(); ++i) {
        cv::Rect boundingBox = cv::boundingRect(contours[i]);

        cv::Point middlePoint(boundingBox.x + boundingBox.width / 2, boundingBox.y + boundingBox.height / 2);
        std::string output = "";
        output += "x: " + std::to_string(middlePoint.x) + " y: " + std::to_string(middlePoint.y) + " time: " + std::to_string(clock() - ticks);
        
        if (printing) {
            std::cout << output << std::endl;
        } else {
            cv::putText(img, output, middlePoint, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 0, 0), 3);

        }
    }

    if (contours.size() == 0) {
        std::string output = "No shapes found";
        output += " time: " + std::to_string(clock() - ticks);

        if (printing) {
            std::cout << output << std::endl;
        } else {
            cv::Point2d middlePoint(img.size().height / 2, img.size().width / 2);
            cv::putText(img, output, middlePoint, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 0, 0), 3);

        }
    }

    cv::imshow("Output", img);
}

void Feed::setTicks(const clock_t ticks) {
    this->ticks = ticks;
}