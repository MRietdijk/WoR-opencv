#ifndef FILE_READER_H__
#define FILE_READER_H__

#include <string>
#include <queue>
#include "Command.h"

class FileReader
{
public:
    explicit FileReader(const std::string& fileName);
    /**
     * @brief Get the Next Command in queue
     * 
     * @return Command 
     */
    Command getNextCommand();
    /**
     * @brief checks if there is a next command in file
     * 
     * @return true there is still a command in queue
     * @return false there is no command in queue
     */
    bool hasNextCommand() const;
    ~FileReader();
private:
    std::queue<Command> commands;
};


#endif