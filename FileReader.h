#ifndef FILE_READER_H__
#define FILE_READER_H__

#include <string>
#include <queue>
#include "Command.h"

class FileReader
{
public:
    FileReader(std::string fileName);
    Command getNextCommand();
    bool hasNextCommand();
    ~FileReader();
private:
    std::queue<Command> commands;
};


#endif