#ifndef FILE_FEED_H__
#define FILE_FEED_H__

#include "Feed.h"

class FileFeed : public Feed
{
public:
    FileFeed(std::string file);
    /**
     * @brief Get the Feed from file
     * 
     * @return cv::Mat 
     */
    cv::Mat getFeed();
    virtual ~FileFeed();
private:
};

#endif