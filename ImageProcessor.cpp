#include "ImageProcessor.h"

// Custom HSV values
const std::array<int, 6> ORANGE_HSV = {0, 110, 148, 60, 242, 255};
const std::array<int, 6> GREEN_HSV = {50, 120, 100, 179, 255, 255};
const std::array<int, 6> YELLOW_HSV = {10, 0, 0, 40, 160, 255};
const std::array<int, 6> PINK_HSV = {130, 10, 70, 179, 255, 255};

ImageProcessor::ImageProcessor() : HSVValues({0, 0, 0, 255, 255, 255}), value(0), saturation(0), hue(0), deviationDistanceCircle(90), squareDeviation(30) {}

ImageProcessor::~ImageProcessor() {}

contoursType ImageProcessor::getContours(const cv::Mat& imgWithEdges) const {
    contoursType contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(imgWithEdges, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    return contours;
}

contoursType ImageProcessor::getContoursFromColor(const Command& cmd, const cv::Mat& img, bool showStepsBetween /* = false */) {
    
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
        cv::imshow("dilate", imgDilate);
    }

    return contours;
}

void ImageProcessor::showSliders() {
    std::string windowName = "Sliders";
    cv::namedWindow(windowName);
    cv::createTrackbar("brightness", windowName, &this->value, 100);
    cv::createTrackbar("saturation", windowName, &this->saturation, 100);
    cv::createTrackbar("hue", windowName, &this->hue, 100);
    // cv::createTrackbar("hmin", windowName, &this->HSVValues[0], 179);
    // cv::createTrackbar("smin", windowName, &this->HSVValues[1], 255);
    // cv::createTrackbar("vmin", windowName, &this->HSVValues[2], 255);
    // cv::createTrackbar("hmax", windowName, &this->HSVValues[3], 179);
    // cv::createTrackbar("smax", windowName, &this->HSVValues[4], 255);
    // cv::createTrackbar("vmax", windowName, &this->HSVValues[5], 255);
    cv::createTrackbar("areaCircle", windowName, &this->deviationDistanceCircle, 1000);
    cv::setTrackbarMin("brightness", windowName, -100);
    cv::setTrackbarMin("saturation", windowName, -100);
    cv::setTrackbarMin("hue", windowName, -100);
}

void ImageProcessor::setHSVValues(const Command& cmd) {
    switch (cmd.getColor())
    {
    case Color::PINK:
        this->HSVValues = PINK_HSV;
        break;
    case Color::GREEN:
        this->HSVValues = GREEN_HSV;
        break;
    case Color::ORANGE:
        this->HSVValues = ORANGE_HSV;
        break;
    case Color::YELLOW:
        this->HSVValues = YELLOW_HSV;
        break;
    default:
        this->HSVValues = ORANGE_HSV;
        break;
    }
    this->HSVValues[0] += this->hue;
    this->HSVValues[1] += this->saturation;
    this->HSVValues[2] += this->value;
    this->HSVValues[3] += this->hue;
    this->HSVValues[4] += this->saturation;
    this->HSVValues[5] += this->value;
}

contoursType ImageProcessor::getContoursFromShape(const Command& cmd, const cv::Mat& img, const contoursType& colorContours, bool showStepsBetween /*= false */) const {
    contoursType result;

    switch (cmd.getShape())
    {
    case Shape::TRIANGLE:
        result = this->findTriangle(colorContours);
        break;
    case Shape::SQUARE:
        result = this->findSquare(colorContours);
        break;
    case Shape::RECTANGLE:
        result = this->findRectangle(colorContours);
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

contoursType ImageProcessor::findTriangle(const contoursType& contours) const {
    contoursType corners(contours.size());
    contoursType result;
    for (uint8_t i = 0; i < contours.size(); ++i) {
        double peri = cv::arcLength(contours[i], true);
        cv::approxPolyDP(contours[i], corners[i], 0.03 * peri, true);

        if (corners[i].size() == 3) {
            result.push_back(contours[i]);
        }
    }

    return result;
}

contoursType ImageProcessor::findSquare(const contoursType& contours) const {
    contoursType corners(contours.size());
    contoursType result;
    for (uint8_t i = 0; i < contours.size(); ++i) {
        double peri = cv::arcLength(contours[i], true);
        cv::approxPolyDP(contours[i], corners[i], 0.03 * peri, true);

        if (corners[i].size() == 4) {
            cv::Rect boundRectangle = cv::boundingRect(corners[i]);
            float aspRatio = std::abs((float)boundRectangle.width - (float)boundRectangle.height);
            if (aspRatio < this->squareDeviation) {
                result.push_back(contours[i]);
            }
        }
    }

    return result;
}

contoursType ImageProcessor::findRectangle(const contoursType& contours) const {
    contoursType corners(contours.size());
    contoursType result;
    for (uint8_t i = 0; i < contours.size(); ++i) {
        double peri = cv::arcLength(contours[i], true);
        cv::approxPolyDP(contours[i], corners[i], 0.03 * peri, true);

        if (corners[i].size() == 4) {
            cv::Rect boundRectangle = cv::boundingRect(corners[i]);
            float aspRatio = std::abs((float)boundRectangle.width - (float)boundRectangle.height);
            if (aspRatio > this->squareDeviation) {
                result.push_back(contours[i]);
            }
        }
    }

    return result;
}

contoursType ImageProcessor::findCircle(const contoursType& contours) const {
    contoursType corners(contours.size());
    contoursType result;
    for (uint8_t i = 0; i < contours.size(); ++i) {
        double peri = cv::arcLength(contours[i], true);
        cv::approxPolyDP(contours[i], corners[i], 0.03 * peri, true);

        if (corners[i].size() > 4 && !hasLongSide(corners[i], this->deviationDistanceCircle)) {
            result.push_back(contours[i]);
        }
    }

    return result;
}

contoursType ImageProcessor::findHalfCircle(const contoursType& contours) const {
    contoursType corners(contours.size());
    contoursType result;
    for (uint8_t i = 0; i < contours.size(); ++i) {
        double peri = cv::arcLength(contours[i], true);
        cv::approxPolyDP(contours[i], corners[i], 0.03 * peri, true);

        if (corners[i].size() > 4 && hasLongSide(corners[i], this->deviationDistanceCircle)) {
            result.push_back(contours[i]);
        }
    }

    return result;
}

bool ImageProcessor::hasLongSide(const std::vector<cv::Point>& corners, double deviation) const {
    std::vector<double> distances(corners.size() - 1);
    for (uint8_t i = 0; i < corners.size(); ++i) {
        std::size_t nexti = (i + 1) % corners.size();

        distances.push_back(std::sqrt(std::pow((corners[i].x - corners[nexti].x), 2) + std::pow((corners[i].y - corners[nexti].y), 2)));
    }

    for (uint8_t i = 0; i < distances.size(); ++i) {
        std::size_t nexti = (i + 1) % distances.size();
        double difference = std::abs(distances[i] - distances[nexti]);

        if (difference > deviation) {
            return true;
        }
    }

    return false;
}