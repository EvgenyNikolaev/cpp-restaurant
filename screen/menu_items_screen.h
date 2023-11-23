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
        const string COMMAND_ADD = "add";
        const string COMMAND_EDIT = "edit";
        const string COMMAND_DELETE = "delete";

        void printList();

        void addMenuItem();

        void deleteMenuItem();

        void editMenuItem();
    };
}

#endif
