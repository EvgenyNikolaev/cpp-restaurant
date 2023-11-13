#include <iostream>
#include "navigation.h"
#include "../helper/view_helper.h"

using namespace std;
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
            cout << command->description->c_str() << " [" << command->command->c_str() << "]" << " | ";
        }
        if (stack->size() == 1) {
            cout << "Exit [" << COMMAND_EXIT << "]";
        } else {
            cout << "Go back [" << COMMAND_BACK << "]";
        }
        ViewHelper::printHorizontalRule();
        string commandInput;
        cin >> commandInput;

        if (commandInput == COMMAND_BACK || commandInput == COMMAND_EXIT) {
            goBack();
            return;
        }

        if (screen->handleCommandInput(commandInput)) {
            return;
        }

        cout << "Incorrect operation. Please try again";
        cin.ignore();
        displayCommandPrompt(screen);
    }

    Navigator::Navigator() {
        stack = new vector<Screen *>();
    }

    void Navigator::putScreenOnStage(Screen *screen) {
        system("cls");

        cout << "Window: " << screen->getName();
        ViewHelper::printHorizontalRule();

        screen->display();
        displayCommandPrompt(screen);
    }

    Command::Command(const string *command, string *description) : description(description),
                                                                             command(command) {
    }

    vector<Command *> *Screen::getCommands() {
        return new vector<Command *>();
    }

}
