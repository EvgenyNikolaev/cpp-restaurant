#ifndef RESTARAUNT_ORDER_SCREEN_H
#define RESTARAUNT_ORDER_SCREEN_H

#include "../service/navigation.h"
#include "../model/order.h"
#include "../model/menu_item.h"

using namespace std;
using namespace service;
using namespace model;

namespace screen {

    class OrderScreen : public Screen {

    public:
        explicit OrderScreen(Order *order);

        void display() override;

        vector<Command *> *getCommands() override;

        bool handleCommandInput(string input) override;

        string getName() override;

    private:
        const string COMMAND_ADD = "add";
        const string COMMAND_REMOVE = "remove";
        const string COMMAND_SERVE = "serve";

        Order *order = nullptr;

        void printOrderMenuItems();

        void addOrderMenuItem();

        void deleteOrderMenuItem();

        void markOrderMenuItemServed();

        void printMenuItemsOptions();
    };

}

#endif
