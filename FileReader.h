#ifndef FILE_READER_H__
#define FILE_READER_H__

#include <string>
#include <queue>
#include "Command.h"

class FileReader
{
public:
    FileReader(const std::string& fileName);
    Command getNextCommand();
    bool hasNextCommand() const;
    ~FileReader();
private:
    std::queue<Command> commands;
};


#endif