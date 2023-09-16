#include <opencv2/opencv.hpp>
#include "CameraFeed.h"
#include "FileFeed.h"
#include <memory>
#include "Input.h"

int main(int argc, char *argv[])
{  
    Input input(argc, argv);
    input.handleInput();
    return 0;
}
