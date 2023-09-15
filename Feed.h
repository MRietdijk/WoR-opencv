#ifndef FEED_H__
#define FEED_H__

#include <string>
#include <opencv2/opencv.hpp>

typedef std::vector<std::vector<cv::Point>> contoursType;

class Feed
{
public:
    Feed(std::string file);
    virtual cv::Mat getFeed() = 0;
    cv::Mat processImg(cv::Mat& img, bool showStepsBetween = false);
    void showSliders();
protected:
    std::string file;
private:
    contoursType getContours(cv::Mat& imgWithEdges);
    int cannyMin;
    int cannyMax;
};


#endif