#include "Feed.h"
#include <array>

// Custom HSV values
std::array<int, 6> orangeHSV = {0, 111, 148, 12, 212, 255};
std::array<int, 6> greenHSV = {67, 115, 90, 81, 180, 196};
std::array<int, 6> yellowHSV = {20, 30, 181, 29, 100, 228};
std::array<int, 6> pinkHSV = {150, 34, 211, 179, 55, 235};


Feed::Feed(std::string file) : file(file), brightness(0), HSVValues({0, 0, 0, 255, 255, 255}), areaCircle(8000), ticks(clock())
{
}

cv::Mat Feed::processImg(cv::Mat& img, bool showStepsBetween /* = false */) {
    cv::Mat imgHSV, imgBlur, imgEdge, result;
    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
    cv::GaussianBlur(imgHSV, imgBlur, cv::Size(7, 7), 3);
    // cv::Canny(imgBlur, imgEdge, this->cannyMin, this->cannyMax);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
    cv::dilate(imgEdge, result, kernel);

    if (showStepsBetween) {
        cv::imshow("HSV", imgHSV);
        cv::imshow("Gaussian", imgBlur);
        cv::imshow("Canny", imgEdge);
        cv::imshow("Dilate", result);
    }

    return result;
}

contoursType Feed::getContours(cv::Mat& imgWithEdges) {
    contoursType contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(imgWithEdges, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    return contours;
}

contoursType Feed::getContoursFromColor(Command& cmd, cv::Mat& img, bool showStepsBetween /* = false */) {
    
    cv::Mat mask, imgHSV, imgBlur, imgErode, imgDilate;
    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
    cv::GaussianBlur(imgHSV, imgBlur, cv::Size(7, 7), 3);

    this->setHSVValues(cmd);

    cv::Scalar lower(HSVValues[0], HSVValues[1], HSVValues[2]);
    cv::Scalar upper(HSVValues[3], HSVValues[4], HSVValues[5]);

    cv::inRange(imgBlur, lower, upper, mask);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));

    cv::erode(mask, imgErode, kernel);
    cv::dilate(imgErode, imgDilate, kernel);

    contoursType contours = getContours(imgDilate);

    
    if (showStepsBetween) {
        // cv::drawContours(img, contours, -1, cv::Scalar(255, 0, 0));
        // cv::imshow("HSV", imgHSV);
        // cv::imshow("Color detection", mask);
        cv::imshow("dilate", imgDilate);
        // cv::imshow("original", img);
    }

    return contours;
}

void Feed::showSliders() {
    std::string windowName = "Sliders";
    cv::namedWindow(windowName);
    cv::createTrackbar("brightness", windowName, &this->brightness, 100);
    cv::createTrackbar("saturation", windowName, &this->saturation, 100);
    cv::createTrackbar("hue", windowName, &this->hue, 100);
    cv::createTrackbar("areaCircle", windowName, &this->areaCircle, 15000);
    cv::setTrackbarMin("brightness", windowName, -100);
    cv::setTrackbarMin("saturation", windowName, -100);
    cv::setTrackbarMin("hue", windowName, -100);
}

void Feed::setHSVValues(Command& cmd) {
    switch (cmd.getColor())
    {
    case Color::PINK:
        this->HSVValues = pinkHSV;
        break;
    case Color::GREEN:
        this->HSVValues = greenHSV;
        break;
    case Color::ORANGE:
        this->HSVValues = orangeHSV;
        break;
    case Color::YELLOW:
        this->HSVValues = yellowHSV;
        break;
    default:
        this->HSVValues = orangeHSV;
        break;
    }
    this->HSVValues[0] += hue;
    this->HSVValues[1] += saturation;
    this->HSVValues[2] += brightness;
    this->HSVValues[3] += hue;
    this->HSVValues[4] += saturation;
    this->HSVValues[5] += brightness;
}

contoursType Feed::getContoursFromShape(Command& cmd, cv::Mat& img, contoursType colorContours, bool showStepsBetween /*= false */) {
    contoursType result;
    float squareDeviation = 0.5;

    switch (cmd.getShape())
    {
    case Shape::TRIANGLE:
        result = this->findTriangle(colorContours);
        break;
    case Shape::SQUARE:
        result = this->findSquare(colorContours, squareDeviation);
        break;
    case Shape::RECTANGLE:
        result = this->findRectangle(colorContours, squareDeviation);
        break;
    case Shape::CIRCLE:
        result = this->findCircle(colorContours);
        break;
    case Shape::HALF_CIRCLE:
        result = this->findHalfCircle(colorContours);
        break;    
    default:
        result = this->findTriangle(colorContours);
        break;
    }

    if (showStepsBetween) {
        cv::drawContours(img, result, -1, cv::Scalar(255, 0, 0));
        cv::imshow("shape contours", img);
    }

    return result;
}

contoursType Feed::findTriangle(contoursType contours) {
    contoursType corners(contours.size());
    contoursType result;
    for (uint8_t i = 0; i < contours.size(); ++i) {
        float peri = cv::arcLength(contours[i], true);
        cv::approxPolyDP(contours[i], corners[i], 0.03 * peri, true);

        if (corners[i].size() == 3) {
            result.push_back(contours[i]);
        }
    }

    return result;
}

contoursType Feed::findSquare(contoursType contours, float deviation) {
    contoursType corners(contours.size());
    contoursType result;
    for (uint8_t i = 0; i < contours.size(); ++i) {
        float peri = cv::arcLength(contours[i], true);
        cv::approxPolyDP(contours[i], corners[i], 0.03 * peri, true);

        if (corners[i].size() == 4) {
            cv::Rect boundRectangle = cv::boundingRect(corners[i]);
            float aspRatio = (float)boundRectangle.width / (float)boundRectangle.height;
            if (aspRatio >  1 - deviation &&  aspRatio < 1 + deviation) {
                result.push_back(contours[i]);
            }
        }
    }

    return result;
}

contoursType Feed::findRectangle(contoursType contours, float deviation) {
    contoursType corners(contours.size());
    contoursType result;
    for (uint8_t i = 0; i < contours.size(); ++i) {
        float peri = cv::arcLength(contours[i], true);
        cv::approxPolyDP(contours[i], corners[i], 0.03 * peri, true);

        if (corners[i].size() == 4) {
            cv::Rect boundRectangle = cv::boundingRect(corners[i]);
            float aspRatio = (float)boundRectangle.width / (float)boundRectangle.height;
            if (aspRatio <  1 - deviation || aspRatio > 1 + deviation) {
                result.push_back(contours[i]);
            }
        }
    }

    return result;
}

contoursType Feed::findCircle(contoursType contours) {
    contoursType corners(contours.size());
    contoursType result;
    for (uint8_t i = 0; i < contours.size(); ++i) {
        float peri = cv::arcLength(contours[i], true);
        cv::approxPolyDP(contours[i], corners[i], 0.03 * peri, true);
        
        int area = cv::contourArea(contours[i]);

        if (corners[i].size() > 4 && area > areaCircle) {
            result.push_back(contours[i]);
        }
    }

    return result;
}

contoursType Feed::findHalfCircle(contoursType contours) {
    contoursType corners(contours.size());
    contoursType result;
    for (uint8_t i = 0; i < contours.size(); ++i) {
        float peri = cv::arcLength(contours[i], true);
        cv::approxPolyDP(contours[i], corners[i], 0.03 * peri, true);
        
        int area = cv::contourArea(contours[i]);

        if (corners[i].size() > 4 && area < areaCircle) {
            result.push_back(contours[i]);
        }
    }

    return result;
}

void Feed::showFound(cv::Mat img, contoursType contours, bool printing /* = false*/) {
    for (uint8_t i = 0; i < contours.size(); ++i) {
        cv::Rect boundingBox = cv::boundingRect(contours[i]);

        cv::Point middlePoint(boundingBox.x + boundingBox.width / 2, boundingBox.y + boundingBox.height / 2);
        std::string output = "";
        output += "x: " + std::to_string(middlePoint.x) + " y: " + std::to_string(middlePoint.y) + " time: " + std::to_string(clock() - ticks);
        
        if (printing) {
            std::cout << output << std::endl;
        } else {
            cv::putText(img, output, middlePoint, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 0, 0), 3);

        }
    }

    if (contours.size() == 0) {
        std::string output = "No shapes found";
        output += " time: " + std::to_string(clock() - ticks);

        if (printing) {
            std::cout << output << std::endl;
        } else {
            cv::Point2d middlePoint(img.size().height / 2, img.size().width / 2);
            cv::putText(img, output, middlePoint, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 0, 0), 3);

        }
    }

    cv::imshow("Output", img);
}

void Feed::setTicks(const clock_t ticks) {
    this->ticks = ticks;
}