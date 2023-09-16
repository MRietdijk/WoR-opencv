#ifndef INPUT_H__
#define INPUT_H__

#include "Command.h"
#include <memory>
#include "Feed.h"

class Input
{
public:
    Input(int argc, char *argv[]);
    ~Input();
    void handleInput();
private:
    std::unique_ptr<Feed> chooseFeed();
    void handleFile();
    void handleCommand();
    static void readConsole(std::string& command, bool& quit);


    int argc;
    char **argv;
};


#endif