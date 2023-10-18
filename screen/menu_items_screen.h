#ifndef RESTARAUNT_MENUITEMS_SCREEN_H
#define RESTARAUNT_MENUITEMS_SCREEN_H

#include "../service/navigation.h"

using namespace service;

namespace screen {
    struct MenuItemsScreen : Screen {
        void display() override;

        std::vector<Command *> *getCommands() override;

        bool handleCommandInput(std::string input) override;

        void printList();

        void addMenuItem();

        void deleteMenuItem();
    };
}

#endif
