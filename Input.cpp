#include "Input.h"
#include "FileReader.h"
#include <thread>
#include <iostream>
#include "CameraFeed.h"
#include "FileFeed.h"
#include <chrono>
#include "ImageProcessor.h"

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

void Input::handleFile() const {
    std::unique_ptr<Feed> feed = chooseFeed();
    std::string fileOfCmds(argv[3]);

    ImageProcessor imgP;

    FileReader fr(fileOfCmds);

    std::chrono::time_point begin =  std::chrono::steady_clock::now();
    const uint16_t DELAY = 1000;
    while (fr.hasNextCommand())
    {
        cv::Mat img = feed->getFeed();
        // give the cam time to start up
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count() <= DELAY) {
            continue;
        }
        begin = std::chrono::steady_clock::now();
        feed->setTicks(clock());
        Command c = fr.getNextCommand();
        contoursType colorContours = imgP.getContoursFromColor(c, img);
        contoursType shapeAndColorContours = imgP.getContoursFromShape(c, img, colorContours, true);
        
        feed->showFound(img, shapeAndColorContours, true);
        cv::waitKey(DELAY);
    }

}

void Input::handleCommand() const {
    std::unique_ptr<Feed> feed = chooseFeed();

    ImageProcessor imgP;
    

    std::string command;
    bool quit = false;


    std::thread consoleThread(readConsole, std::ref(command), std::ref(quit));

    imgP.showSliders();

    while (!quit)
    {
        feed->setTicks(clock());
        if (command.empty()) {
            continue;
        }

        std::string::size_type pos = command.find_last_of(" ");

        std::string shapeStr = command.substr(0, pos);
        std::string colorStr = command.substr(pos + 1);

        Command command(colorStr, shapeStr);

        cv::Mat img = feed->getFeed();
        contoursType colorContours = imgP.getContoursFromColor(command, img, true);
        
        contoursType shapeAndColorContours = imgP.getContoursFromShape(command, img, colorContours, true);
        
        feed->showFound(img, shapeAndColorContours);

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

std::unique_ptr<Feed> Input::chooseFeed() const {
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