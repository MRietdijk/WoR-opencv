#include <opencv2/opencv.hpp>
#include "CameraFeed.h"
#include "FileFeed.h"
#include <memory>
#include "Input.h"

int main(int argc, char *argv[])
{   
    // std::string feedChoice(argv[1]);
    // std::string file(argv[2]);

    // std::cout << argv[1] << std::endl;
    // if (argc != 3) {
    //     std::cout << "not enough parameters" << std::endl;
    //     return -1;
    // }

    // std::unique_ptr<Feed> feed;
    
    // if (feedChoice == "camera") {
    //     std::cout << argv[2] << std::endl;
    //     feed = std::make_unique<CameraFeed>(file);
    // }
    // else if (feedChoice == "file") {
    //     feed = std::make_unique<FileFeed>(file);
    // }

    // feed->showSliders();

    // while (true)
    // {
    //     cv::Mat img = feed->getFeed();
    //     cv::imshow("Feed", img);
    //     img = feed->processImg(img, true);
    //     cv::waitKey(1);
    // }
    

    // cv::destroyAllWindows();



    Input input(argc, argv);

    input.handleInput();
















    return 0;
}
