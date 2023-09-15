#include "Feed.h"

Feed::Feed(std::string file) : file(file), cannyMin(32), cannyMax(49)
{
}

cv::Mat Feed::processImg(cv::Mat& img, bool showStepsBetween /* = false */) {
    cv::Mat imgHSV, imgBlur, imgEdge, result;
    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
    cv::GaussianBlur(imgHSV, imgBlur, cv::Size(7, 7), 3);
    cv::Canny(imgBlur, imgEdge, this->cannyMin, this->cannyMax);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::dilate(imgEdge, result, kernel);

    if (showStepsBetween) {
        cv::imshow("HSV", imgHSV);
        cv::imshow("Gaussian", imgBlur);
        cv::imshow("Canny", imgEdge);
        cv::imshow("Dilate", result);
    }

    return result;
}

contoursType getContours(cv::Mat& imgWithEdges) {
    contoursType contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(imgWithEdges, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    return contours;
}

void Feed::showSliders() {
    std::string windowName = "Sliders";
    cv::namedWindow(windowName);
    cv::createTrackbar("cannyMin", windowName, &this->cannyMin, 255);
    cv::createTrackbar("cannyMax", windowName, &this->cannyMax, 255);
}