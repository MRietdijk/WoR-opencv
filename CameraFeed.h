#ifndef CAMERA_FEED_H__
#define CAMERA_FEED_H__

#include "Feed.h"

class CameraFeed : public Feed
{
public:
    CameraFeed(std::string file);
    cv::Mat getFeed();
    virtual ~CameraFeed();
private:
    cv::VideoCapture cap;
};


#endif