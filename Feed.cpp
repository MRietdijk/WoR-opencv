#include "Feed.h"

Feed::Feed(std::string file) : file(file), cannyMin(32), cannyMax(49)
{
}

cv::Mat& Feed::processImg(cv::Mat& img) {
    cv::Mat imgHSV, imgBlur, imgEdge, imgDil;
    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
    cv::GaussianBlur(imgHSV, imgBlur, cv::Size(7, 7), 3);
    cv::Canny(imgBlur, imgEdge, this->cannyMin, this->cannyMax);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::dilate(imgEdge, img, kernel);

    return img;
}