#include "Input.h"
#include "FileReader.h"
#include <thread>
#include <iostream>
#include "CameraFeed.h"
#include "FileFeed.h"

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
    std::unique_ptr<Feed> feed = chooseFeed();
    std::string fileOfCmds(argv[3]);

    FileReader fr(fileOfCmds);

    while (fr.hasNextCommand())
    {
        Command c = fr.getNextCommand();
    }
    

}

void Input::handleCommand() {
    std::unique_ptr<Feed> feed = chooseFeed();

    std::string command;
    bool quit = false;


    std::thread consoleThread(readConsole, std::ref(command), std::ref(quit));

    feed->showSliders();
    while (!quit)
    {
        if (command.empty()) {
            continue;
        }

        std::string::size_type pos = command.find_last_of(" ");

        std::string shapeStr = command.substr(0, pos);
        std::string colorStr = command.substr(pos + 1);

        Command command(colorStr, shapeStr);

        cv::Mat img = feed->getFeed();
        // cv::imshow("Feed", img);
        // img = feed->processImg(img, true);
        contoursType colorContours = feed->getContoursFromColor(command, img, true);
        
        contoursType shapeAndColorContours = feed->getContoursFromShape(command, img, colorContours, true);
        
        cv::waitKey(1);
    }
    cv::destroyAllWindows();

    consoleThread.join();
}

/* static */ void Input::readConsole(std::string& command, bool& quit) {
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

std::unique_ptr<Feed> Input::chooseFeed() {
    std::string feedChoice(argv[1]);
    std::string fileOfImg(argv[2]);

    if (feedChoice == "camera") {
        return std::make_unique<CameraFeed>(fileOfImg);
    }
    else if (feedChoice == "file") {
        return std::make_unique<FileFeed>(fileOfImg);
    }
    
    return std::make_unique<FileFeed>(fileOfImg);
}