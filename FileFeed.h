#ifndef FILE_FEED_H__
#define FILE_FEED_H__

#include "Feed.h"

class FileFeed : public Feed
{
public:
    explicit FileFeed(const std::string& file);
    /**
     * @brief Get the Feed from file
     * 
     * @return cv::Mat 
     */
    cv::Mat getFeed() override;
    virtual ~FileFeed();
private:
};

#endif