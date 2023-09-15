#ifndef FILE_FEED_H__
#define FILE_FEED_H__

#include "Feed.h"

class FileFeed : public Feed
{
public:
    FileFeed(std::string file);
    cv::Mat getFeed();
    virtual ~FileFeed();
private:
};

#endif