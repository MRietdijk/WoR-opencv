#include "FileReader.h"
#include <fstream>
#include <iostream>

FileReader::FileReader(std::string fileName) {

    std::string line;    
    std::ifstream file(fileName);

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::string::size_type pos = line.find_last_of(" ");

        std::string shapeStr = line.substr(0, pos);
        std::string colorStr = line.substr(pos + 1);

        Command c(colorStr, shapeStr);
        this->commands.push(c);
    }
    
}

bool FileReader::hasNextCommand() {
    return this->commands.size() > 0;
}

Command FileReader::getNextCommand() {
    Command c = this->commands.front();
    std::cout << "<<command: " + c.getShapeStr() << " " << c.getColorStr() << ">>" << std::endl;
    this->commands.pop();
    return c;
}

FileReader::~FileReader() {}