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
    Command();
    Command(std::string colorStr, std::string shapeStr);
    /**
     * @brief Get the Color object
     * 
     * @return Color 
     */
    Color getColor() const;
    /**
     * @brief Get the Shape object
     * 
     * @return Shape 
     */
    Shape getShape() const;
    /**
     * @brief Get the Color Str object
     * 
     * @return std::string 
     */
    std::string getColorStr() const;
    /**
     * @brief Get the Shape Str object
     * 
     * @return std::string 
     */
    std::string getShapeStr() const;
    ~Command();
private:
    /**
     * @brief converts string to color
     * 
     * @param colorStr 
     */
    void strToColor(const std::string& colorStr);
    /**
     * @brief converts string to shape
     * 
     * @param shapeStr 
     */
    void strToShape(const std::string& shapeStr);

    Color color;
    Shape shape;
    std::string colorStr;
    std::string shapeStr;
};

#endif