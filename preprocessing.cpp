#include <opencv2/opencv.hpp>


cv::Mat img, imgGray, imgBlur, imgEdge, imgDil;
cv::VideoCapture cap;

int cannyMin = 32;
int cannyMax = 49;
int contourArea = 5600;

void getContours(cv::Mat processedImg, cv::Mat img) {
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(processedImg, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::vector<std::vector<cv::Point>> corners(contours.size());
    
    std::vector<cv::Rect> boundingBorders(contours.size());
    
    for (uint8_t i = 0; i < contours.size(); ++i) {
        int area = cv::contourArea(contours[i]);
        
        if (area > contourArea) {
            // corner detection
            float peri = cv::arcLength(contours[i], true);
            cv::approxPolyDP(contours[i], corners[i], 0.02 * peri, true);

            cv::drawContours(img, contours, i, cv::Scalar(255, 0, 255), 1);
            if (corners[i].size() == 3) {
                boundingBorders[i] = cv::boundingRect(corners[i]);

                cv::Point txtCordinate(boundingBorders[i].x + boundingBorders[i].width / 2, boundingBorders[i].y + boundingBorders[i].height / 2);
                cv::putText(img, "Triangle", txtCordinate, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 0, 0));
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    cap.open("/dev/video2");
    cv::namedWindow("Thresholds");
    cv::createTrackbar("cannyMin", "Thresholds", &cannyMin, 255);
    cv::createTrackbar("cannyMax", "Thresholds", &cannyMax, 255);
    cv::createTrackbar("contourArea", "Thresholds", &contourArea, 10000);
    
    
    while(true) {
        cap.read(img);
        
        // preprocessing
        cv::cvtColor(img, imgGray, cv::COLOR_BGR2HSV);
        cv::GaussianBlur(imgGray, imgBlur, cv::Size(7, 7), 3);
        cv::Canny(imgBlur, imgEdge, cannyMin, cannyMax);
        // cv::Sobel(imgBlur, imgEdge, CV_8U, 1, 1);
        // cv::Laplacian(imgBlur, imgEdge, CV_8U, 1, 10);

        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        cv::dilate(imgEdge, imgDil, kernel);
        getContours(imgDil, img);
        cv::imshow("Original", img);
        cv::imshow("Gray", imgGray);
        cv::imshow("Blur", imgBlur);
        cv::imshow("Edge detection", imgEdge);
        cv::imshow("Dilate", imgDil);

        cv::waitKey(1);

    }
    return 0;
}
