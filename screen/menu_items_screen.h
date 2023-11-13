#ifndef RESTARAUNT_MENUITEMS_SCREEN_H
#define RESTARAUNT_MENUITEMS_SCREEN_H

#include "../service/navigation.h"

using namespace service;

namespace screen {
    class MenuItemsScreen : public Screen {
    public:
        void display() override;

        std::vector<Command *> *getCommands() override;

        bool handleCommandInput(std::string input) override;

        std::string getName() override;

    private:
        constexpr static const std::string COMMAND_ADD = "add";
        constexpr static const std::string COMMAND_EDIT = "edit";
        constexpr static const std::string COMMAND_DELETE = "delete";

        void printList();

        void addMenuItem();

        void deleteMenuItem();

        void editMenuItem();
    };
}

#endif
