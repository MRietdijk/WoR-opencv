#include "Input.h"
#include "FileReader.h"
#include <thread>
#include <iostream>

Input::Input(int argc, char *argv[]) : argc(argc), argv(argv) {
}

Input::~Input() {}

void Input::handleInput() {
    if (argc == 4) {
        handleFile();
    } else if (argc == 3) {
        handleCommand();
    }
}

void Input::handleFile() {
    std::string feedChoice(argv[1]);
    std::string fileOfImg(argv[2]);
    std::string fileOfCmds(argv[3]);

    FileReader fr(fileOfCmds);

    while (fr.hasNextCommand())
    {
        Command c = fr.getNextCommand();
    }
    

}

void Input::handleCommand() {
    std::string command;
    bool quit = false;

    std::thread consoleThread(readConsole, std::ref(command), std::ref(quit));

    while (!quit)
    {
        if (!command.empty()) {
            std::string::size_type pos = command.find_last_of(" ");

            std::string shapeStr = command.substr(0, pos);
            std::string colorStr = command.substr(pos + 1);
        }
    }

    consoleThread.join();
    
}

void Input::readConsole(std::string& command, bool& quit) {
    std::string userInput = "";
    while (userInput != "q")
    {
        std::cout << "Type a command (q to quit):" << std::endl;

        std::getline(std::cin, userInput);

        if (userInput == "q") {
            quit = true;
            break;
        }

        command = userInput;
    }
}