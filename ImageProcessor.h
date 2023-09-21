#ifndef IMAGEPROCESSOR_H__
#define IMAGEPROCESSOR_H__

#include <opencv2/opencv.hpp>
typedef std::vector<std::vector<cv::Point>> contoursType;
#include "Command.h"


class ImageProcessor
{
public:
    ImageProcessor();
    contoursType getContoursFromColor(Command& cmd, cv::Mat& img, bool showStepsBetween = false);
    contoursType getContoursFromShape(Command& cmd, cv::Mat& img, contoursType colorContours, bool showStepsBetween = false);
    void showSliders();
    contoursType getContours(cv::Mat& imgWithEdges);
    void setHSVValues(Command& cmd);
    ~ImageProcessor();
private:
    contoursType findTriangle(contoursType contours);
    contoursType findRectangle(contoursType contours);
    contoursType findHalfCircle(contoursType contours);
    contoursType findCircle(contoursType contours);
    contoursType findSquare(contoursType contours);
    bool hasLongSide(std::vector<cv::Point>& corners, double deviation) const;
    
    // attributes
    std::array<int, 6> HSVValues;
    int value;
    int saturation;
    int hue;
    int deviationDistanceCircle;
    float squareDeviation; 
};


#endif