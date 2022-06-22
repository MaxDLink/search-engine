//
// Created by Max Link on 6/22/22.
//

#include "Interface.h"
#include "iostream"



void Interface::userInterface() {
    std::string userInput = "1";
    while (userInput != "0") {
        std::cout << "1. clear index" << std::endl << "2. manage persistent index" << std::endl
                  << "3. parse to populate index" << std::endl << "4. parse to read from persistence file" << std::endl
                  << "5. enter bool query" << std::endl << "6. output statistics" << std::endl << "0. Quit"
                  << std::endl;

        getline(std::cin, userInput);

        if (userInput == "1") {
            std::cout << "clearing index" << std::endl;
        } else if (userInput == "2") {
            std::cout << "managing persistent index" << std::endl;
        } else if (userInput == "3") {
            std::cout << "parsing to populate index" << std::endl;
        } else if (userInput == "4") {
            std::cout << "parsing to read from persistence file" << std::endl;
        } else if (userInput == "5") {
            std::cout << "enter query here: " << std::flush;
            getline(std::cin, userInput);
            std::cout << userInput << std::endl;
        } else if (userInput == "6") {
            std::cout << "outputting stats" << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "exiting program" << std::endl;
}