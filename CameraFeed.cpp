#include "CameraFeed.h"

CameraFeed::CameraFeed(std::string file) : Feed(file) {
    this->cap.open(file);
}

cv::Mat CameraFeed::getFeed() {
    cv::Mat img;
    this->cap.read(img);
    return img;
}

CameraFeed::~CameraFeed() {}