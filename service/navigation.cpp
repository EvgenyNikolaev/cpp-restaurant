#include <iostream>
#include "navigation.h"
#include "../helper/view_helper.h"

using namespace helper;

namespace service {
    Navigator *Navigator::instance = nullptr;

    Navigator *Navigator::getInstance() {
        if (instance == nullptr) {
            instance = new Navigator();
        }
        return instance;
    }

    void Navigator::navigate(Screen *screen, bool replace) {
        if (replace) {
            stack->pop_back();
        }
        stack->push_back(screen);
        putScreenOnStage(screen);
    }

    void Navigator::goBack() {
        if (stack->size() == 1) {
            exit(0);
        }
        stack->pop_back();
        auto screen = stack->at(stack->size() - 1);
        putScreenOnStage(screen);
    }

    void Navigator::displayCommandPrompt(Screen *screen) {
        ViewHelper::printHorizontalRule();
        for (auto command: *screen->getCommands()) {
            std::cout << command->description->c_str() << " [" << command->command->c_str() << "]" << " | ";
        }
        if (stack->size() == 1) {
            std::cout << "Exit [" << COMMAND_EXIT << "]";
        } else {
            std::cout << "Go back [" << COMMAND_BACK << "]";
        }
        ViewHelper::printHorizontalRule();
        std::string commandInput;
        std::cin >> commandInput;

        if (commandInput == COMMAND_BACK || commandInput == COMMAND_EXIT) {
            goBack();
            return;
        }

        if (screen->handleCommandInput(commandInput)) {
            return;
        }

        std::cout << "Incorrect operation. Please try again";
        std::cin.ignore();
        displayCommandPrompt(screen);
    }

    Navigator::Navigator() {
        stack = new std::vector<Screen *>();
    }

    void Navigator::putScreenOnStage(Screen *screen) {
        system("cls");

        std::cout << "Window: " << screen->getName();
        ViewHelper::printHorizontalRule();

        screen->display();
        displayCommandPrompt(screen);
    }

    Command::Command(const std::string *command, std::string *description) : description(description),
                                                                             command(command) {
    }

    std::vector<Command *> *Screen::getCommands() {
        return new std::vector<Command *>();
    }

}
