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
    /**
     * @brief Get the Feed object from camera or image
     * 
     * @return cv::Mat 
     */
    virtual cv::Mat getFeed() = 0;
    /**
     * @brief show found contrours
     * 
     * @param img the image to put output
     * @param contours the contours from the shapes
     * @param printing if the x, y and clockticks need to be printed
     */
    void showFound(cv::Mat img, contoursType contours, bool printing = false) const;
    /**
     * @brief Set the Ticks object
     * 
     * @param ticks 
     */
    void setTicks(const clock_t ticks);
protected:
    std::string file;
private:
    clock_t ticks;
};


#endif