#include <opencv2/opencv.hpp>

cv::VideoCapture cap;

cv::Mat img;

int main(int argc, char const *argv[])
{
    cap.open("/dev/video0");
    while (true)
    {
        cap.read(img);
        cv::imshow("cam", img);
        cv::waitKey(1);
    }
    

}