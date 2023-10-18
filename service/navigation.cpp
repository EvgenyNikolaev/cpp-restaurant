#include <iostream>
#include "navigation.h"

namespace service {
    Navigator *Navigator::instance = nullptr;

    Navigator *Navigator::getInstance() {
        if (instance == nullptr) {
            instance = new Navigator();
        }
        return instance;
    }

    void Navigator::navigate(Screen *screen) {
        stack->push_back(screen);
        system("cls");

        screen->display();
        displayCommandPrompt(screen);
    }

    void Navigator::goBack() {
        if (stack->size() == 1) {
            exit(0);
        }
        stack->pop_back();
        auto screen = stack->at(stack->size() - 1);
        navigate(screen);
    }

    void Navigator::displayCommandPrompt(Screen *screen) {
        std::cout << "Available operations:\n";
        for (auto command: *screen->getCommands()) {
            std::cout << command->description->c_str() << ", ";
        }
        if (stack->size() == 1) {
            std::cout << "Exit (e)";
        } else {
            std::cout << "Go back (b)";
        }

        std::cout << std::endl;
        std::string commandInput;
        std::cin >> commandInput;

        if (commandInput == "b" || commandInput == "e") {
            goBack();
            return;
        }

        if (screen->handleCommandInput(commandInput)) {
            return;
        }

        std::cout << "Incorrect operation. Please try again\n";
        displayCommandPrompt(screen);
    }

    Navigator::Navigator() {
        stack = new std::vector<Screen *>();
    }

    Command::Command(std::string *description) : description(description) {
    }

    std::vector<Command *> *Screen::getCommands() {
        return new std::vector<Command *>();
    }

}
