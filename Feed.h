#ifndef FEED_H__
#define FEED_H__

#include <string>
#include <opencv2/opencv.hpp>

class Feed
{
public:
    Feed(std::string file);
    virtual cv::Mat getFeed() = 0;
    cv::Mat& processImg(cv::Mat& img);
protected:
    std::string file;
private:
    uint8_t cannyMin;
    uint8_t cannyMax;
};


#endif