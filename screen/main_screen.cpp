#include <iostream>
#include "main_screen.h"
#include "orders_list_screen.h"
#include "menu_items_screen.h"

using namespace std;
using namespace service;
using namespace repository;

namespace screen {
    void MainScreen::display() {
        cout << "Welcome!";
    }

    bool MainScreen::handleCommandInput(string input) {
        if (input == COMMAND_MENU) {
            Navigator::getInstance()->navigate(new MenuItemsScreen());
            return true;
        } else if (input == COMMAND_ORDERS) {
            Navigator::getInstance()->navigate(new OrdersListScreen());
            return true;
        }
        return false;
    }

    vector<Command *> *MainScreen::getCommands() {
        auto commands = Screen::getCommands();

        commands->push_back(new Command(&COMMAND_MENU, new string("Review menu items")));
        commands->push_back(new Command(&COMMAND_ORDERS, new string("Review menu items")));
        return commands;
    }

    string MainScreen::getName() {
        return "Main screen";
    }
}
