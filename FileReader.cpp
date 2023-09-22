#include "FileReader.h"
#include <fstream>
#include <iostream>

FileReader::FileReader(const std::string& fileName) {

    std::string line;    
    std::ifstream file(fileName);

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::string::size_type pos = 0;

        std::string colorStr = "";

        if (line.find_first_of("#") != std::string::npos) {
            pos = line.find_last_of(" ", line.find_first_of("#") - 1);
            colorStr = line.substr(pos + 1, line.find_first_of("#") - (pos + 1));
        } else {
            pos = line.find_last_of(" ");
            colorStr = line.substr(pos + 1);
        }


        std::string shapeStr = line.substr(0, pos);

        Command c(colorStr, shapeStr);
        this->commands.push(c);
    }
    
}

bool FileReader::hasNextCommand() const {
    return this->commands.size() > 0;
}

Command FileReader::getNextCommand() {
    Command c = this->commands.front();
    std::cout << "<<command: " + c.getShapeStr() << " " << c.getColorStr() << ">>" << std::endl;
    this->commands.pop();
    return c;
}

FileReader::~FileReader() {}