#include <opencv2/opencv.hpp>

cv::Mat img, imgHSV, mask;

int hmin, smin, vmin = 0;
int hmax = 179;
int smax, vmax = 255;

const std::string trackbarWinName = "trackbars";

int main(int argc, char const *argv[])
{   
    img = cv::imread("img.png");


    cv::namedWindow(trackbarWinName, (500, 1000));

    cv::createTrackbar("hmin", trackbarWinName, &hmin, 179);
    cv::createTrackbar("smin", trackbarWinName, &smin, 255);
    cv::createTrackbar("vmin", trackbarWinName, &vmin, 255);
    cv::createTrackbar("hmax", trackbarWinName, &hmax, 179);
    cv::createTrackbar("smax", trackbarWinName, &smax, 255);
    cv::createTrackbar("vmax", trackbarWinName, &vmax, 255);

    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

    while (true)
    {
        cv::Scalar lower(hmin, smin, vmin);
        cv::Scalar upper(hmax, smax, vmax);

        cv::inRange(imgHSV, lower, upper, mask);

        cv::imshow("Original", img);
        cv::imshow("HSV", imgHSV);
        cv::imshow("Mask", mask);
        cv::waitKey(1);
    }
    

    cv::destroyAllWindows();
}