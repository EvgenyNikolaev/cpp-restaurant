#ifndef RESTARAUNT_CREATE_ORDER_SCREEN_H
#define RESTARAUNT_CREATE_ORDER_SCREEN_H

#include "../service/navigation.h"

using namespace service;

namespace screen {

    struct CreateOrderScreen : Screen {
        void display() override;

        std::vector<Command *> *getCommands() override;

        bool handleCommandInput(std::string input) override;

        std::string getName() override;
    };

}

#endif
