#ifndef FEED_H__
#define FEED_H__

#include <string>
#include <opencv2/opencv.hpp>
#include "Command.h"
#include <time.h>

typedef std::vector<std::vector<cv::Point>> contoursType;

class Feed
{
public:
    Feed(std::string file);
    virtual cv::Mat getFeed() = 0;
    void showFound(cv::Mat img, contoursType contours, bool printing = false) const;
    void setTicks(const clock_t ticks);
protected:
    std::string file;
private:
    clock_t ticks;
};


#endif