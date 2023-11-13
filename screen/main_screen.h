#ifndef RESTARAUNT_MAIN_SCREEN_H
#define RESTARAUNT_MAIN_SCREEN_H

#include "../service/navigation.h"

using namespace service;

namespace screen {
    class MainScreen : public Screen {
    public:
        void display() override;

        std::vector<Command *> *getCommands() override;

        bool handleCommandInput(std::string input) override;

        std::string getName() override;
    private:
        constexpr static const std::string COMMAND_MENU = "menu";
        constexpr static const std::string COMMAND_ORDERS = "orders";
    };
}

#endif
