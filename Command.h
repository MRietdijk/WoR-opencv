#ifndef COMMAND_H__
#define COMMAND_H__

#include <string>

typedef enum {
    GREEN,
    PINK,
    YELLOW,
    ORANGE,
} Color;

typedef enum {
    CIRCLE,
    HALF_CIRCLE,
    RECTANGLE,
    TRIANGLE,
    SQUARE,
} Shape;

class Command
{
public:
    Command(std::string colorStr, std::string shapeStr);
    ~Command();
private:
    void strToColor(const std::string& colorStr);
    void strToShape(const std::string& shapeStr);

    Color color;
    Shape shape;
};

#endif