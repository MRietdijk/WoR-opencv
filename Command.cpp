#include "Command.h"
#include <iostream>


Command::Command() : color(Color::ORANGE), shape(Shape::TRIANGLE), colorStr("oranje"), shapeStr("driehoek") {}

Command::Command(std::string colorStr, std::string shapeStr) : colorStr(colorStr), shapeStr(shapeStr) {
    this->strToColor(colorStr);
    this->strToShape(shapeStr);
}

Command::~Command()
{
}

void Command::strToColor(const std::string& colorStr) {
    Color result;

    if (colorStr == "groen") {
        result = Color::GREEN;
    } else if (colorStr == "roze") {
        result = Color::PINK;
    } else if (colorStr == "geel") {
        result = Color::YELLOW;
    } else if (colorStr == "oranje") {
        result = Color::ORANGE;
    }

    this->color = result;
}

void Command::strToShape(const std::string& shapeStr) {
    Shape result;
    
    if (shapeStr == "cirkel") {
        result = Shape::CIRCLE;
    } else if (shapeStr == "halve cirkel") {
        result = Shape::HALF_CIRCLE;
    } else if (shapeStr == "vierkant") {
        result = Shape::SQUARE;
    } else if (shapeStr == "rechthoek") {
        result = Shape::RECTANGLE;
    } else if (shapeStr == "driehoek") {
        result = Shape::TRIANGLE;
    }

    this->shape = result;
}


Color Command::getColor() const {
    return this->color;
}

Shape Command::getShape() const {
    return this->shape;
}

std::string Command::getColorStr() const {
    return this->colorStr;
}
    
std::string Command::getShapeStr() const {
    return this->shapeStr;
}