#ifndef IMAGEPROCESSOR_H__
#define IMAGEPROCESSOR_H__

#include <opencv2/opencv.hpp>
typedef std::vector<std::vector<cv::Point>> contoursType;
#include "Command.h"


class ImageProcessor
{
public:
    ImageProcessor();
    contoursType getContoursFromColor(const Command& cmd, const cv::Mat& img, bool showStepsBetween = false);
    contoursType getContoursFromShape(const Command& cmd, const cv::Mat& img, const contoursType& colorContours, bool showStepsBetween = false) const;
    void showSliders();
    contoursType getContours(const cv::Mat& imgWithEdges) const;
    void setHSVValues(const Command& cmd);
    ~ImageProcessor();
private:
    contoursType findTriangle(const contoursType& contours) const;
    contoursType findRectangle(const contoursType& contours) const;
    contoursType findHalfCircle(const contoursType& contours) const;
    contoursType findCircle(const contoursType& contours) const;
    contoursType findSquare(const contoursType& contours) const;
    bool hasLongSide(const std::vector<cv::Point>& corners, double deviation) const;
    
    // attributes
    std::array<int, 6> HSVValues;
    int value;
    int saturation;
    int hue;
    int deviationDistanceCircle;
    float squareDeviation; 
};


#endif