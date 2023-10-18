#ifndef RESTARAUNT_MAIN_SCREEN_H
#define RESTARAUNT_MAIN_SCREEN_H

#include "../service/navigation.h"

using namespace service;

namespace screen {
    struct MainScreen : Screen {
        void display() override;

        std::vector<Command *> *getCommands() override;

        bool handleCommandInput(std::string input) override;
    };
}

#endif
