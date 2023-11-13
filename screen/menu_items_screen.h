#ifndef RESTARAUNT_MENUITEMS_SCREEN_H
#define RESTARAUNT_MENUITEMS_SCREEN_H

#include "../service/navigation.h"

using namespace std;
using namespace service;

namespace screen {
    class MenuItemsScreen : public Screen {
    public:
        void display() override;

        vector<Command *> *getCommands() override;

        bool handleCommandInput(string input) override;

        string getName() override;

    private:
        constexpr static const string COMMAND_ADD = "add";
        constexpr static const string COMMAND_EDIT = "edit";
        constexpr static const string COMMAND_DELETE = "delete";

        void printList();

        void addMenuItem();

        void deleteMenuItem();

        void editMenuItem();
    };
}

#endif
