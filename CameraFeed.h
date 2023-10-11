#ifndef CAMERA_FEED_H__
#define CAMERA_FEED_H__

#include "Feed.h"

class CameraFeed : public Feed
{
public:
    explicit CameraFeed(std::string file);
    /**
     * @brief gives the next image from camera
     * 
     * @return cv::Mat 
     */
    cv::Mat getFeed() override;
    virtual ~CameraFeed();
private:
    cv::VideoCapture cap;
};


#endif