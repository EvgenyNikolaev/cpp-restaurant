#ifndef RESTARAUNT_MAIN_SCREEN_H
#define RESTARAUNT_MAIN_SCREEN_H

#include "../service/navigation.h"

using namespace std;
using namespace service;

namespace screen {
    class MainScreen : public Screen {
    public:
        void display() override;

        vector<Command *> *getCommands() override;

        bool handleCommandInput(string input) override;

        string getName() override;
    private:
        const string COMMAND_MENU = "menu";
        const string COMMAND_ORDERS = "orders";
    };
}

#endif
