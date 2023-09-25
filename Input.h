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
    /**
     * @brief function to run it all
     * 
     */
    void handleInput();
private:
    /**
     * @brief based on args chooses which feed it will pick
     * 
     * @return std::unique_ptr<Feed> 
     */
    std::unique_ptr<Feed> chooseFeed() const;
    /**
     * @brief handles a command file
     * 
     */
    void handleFile() const;
    /**
     * @brief handles a single command
     * 
     */
    void handleCommand() const;
    /**
     * @brief reads the console input
     * 
     * @param command 
     * @param quit 
     */
    static void readConsole(std::string& command, bool& quit);


    int argc;
    char **argv;
};


#endif