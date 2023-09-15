#include "FileFeed.h"

FileFeed::FileFeed(std::string file) : Feed(file)
{
}

FileFeed::~FileFeed()
{
}

cv::Mat FileFeed::getFeed() {
    cv::Mat img = cv::imread(this->file);
    cv::resize(img, img, cv::Size(500, 300));
    return img;
}