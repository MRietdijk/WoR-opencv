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
    cv::Mat processImg(cv::Mat& img, bool showStepsBetween = false);
    contoursType getContoursFromColor(Command& cmd, cv::Mat& img, bool showStepsBetween = false);
    contoursType getContoursFromShape(Command& cmd, cv::Mat& img, contoursType colorContours, bool showStepsBetween = false);
    void showSliders();
    void showFound(cv::Mat img, contoursType contours, bool printing = false);
    void setTicks(const clock_t ticks);
protected:
    std::string file;
    std::array<int, 6> HSVValues;
private:
    contoursType getContours(cv::Mat& imgWithEdges);
    void setHSVValues(Command& cmd);
    contoursType findTriangle(contoursType contours);
    contoursType findRectangle(contoursType contours, float deviation);
    contoursType findHalfCircle(contoursType contours);
    contoursType findCircle(contoursType contours);
    contoursType findSquare(contoursType contours, float deviation);
    bool hasLongSide(std::vector<cv::Point>& corners, double deviation) const;
    int brightness;
    int saturation;
    int hue;
    int deviationDistanceCircle;
    clock_t ticks;
};


#endif