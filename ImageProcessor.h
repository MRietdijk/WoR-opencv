#ifndef IMAGEPROCESSOR_H__
#define IMAGEPROCESSOR_H__

#include <opencv2/opencv.hpp>
typedef std::vector<std::vector<cv::Point>> contoursType;
#include "Command.h"


class ImageProcessor
{
public:
    ImageProcessor();
    /**
     * @brief Get the Contours From Color
     * 
     * @param cmd the command send in terminal
     * @param img the output img
     * @param showStepsBetween if the imshows of different filters will be shown
     * @return contoursType 
     */
    contoursType getContoursFromColor(const Command& cmd, const cv::Mat& img, bool showStepsBetween = false);
    /**
     * @brief Get the Contours From Shape
     * 
     * @param cmd 
     * @param img 
     * @param colorContours the contours from getContoursFromColor
     * @param showStepsBetween 
     * @return contoursType 
     */
    contoursType getContoursFromShape(const Command& cmd, const cv::Mat& img, const contoursType& colorContours, bool showStepsBetween = false) const;
    /**
     * @brief shows the sliders for filters
     * 
     */
    void showSliders();
    /**
     * @brief Get the Contours from img
     * 
     * @param imgWithEdges 
     * @return contoursType 
     */
    contoursType getContours(const cv::Mat& imgWithEdges) const;
    /**
     * @brief gets cmd command and sets the HSV attributes based on the cmd command
     * 
     * @param cmd 
     */
    void setHSVValues(const Command& cmd);
    ~ImageProcessor();
private:
    /**
     * @brief gives back contours that look like a triangle
     * 
     * @param contours 
     * @return contoursType 
     */
    contoursType findTriangle(const contoursType& contours) const;
    /**
     * @brief gives back contours that look like a rectangle
     * 
     * @param contours 
     * @return contoursType 
     */
    contoursType findRectangle(const contoursType& contours) const;
    /**
     * @brief gives back contours that look like a circle
     * 
     * @param contours 
     * @return contoursType 
     */
    contoursType findHalfCircle(const contoursType& contours) const;
    /**
     * @brief gives back contours that look like a half cirkel
     * 
     * @param contours 
     * @return contoursType 
     */
    contoursType findCircle(const contoursType& contours) const;
    /**
     * @brief gives back contours that look like a square
     * 
     * @param contours 
     * @return contoursType 
     */
    contoursType findSquare(const contoursType& contours) const;
    /**
     * @brief checks if 2 corners are much further apart from each other than the rest
     * 
     * @param corners 
     * @param deviation the deviation between the two points
     * @return true 
     * @return false 
     */
    bool hasLongSide(const std::vector<cv::Point>& corners, double deviation) const;
    
    // attributes
    std::array<int, 6> HSVValues;
    int value;
    int saturation;
    int hue;
    int deviationDistanceCircle;
    int squareDeviation; 
};


#endif