#include <iostream>
#include "main_screen.h"
#include "orders_list_screen.h"
#include "menu_items_screen.h"

using namespace service;

namespace screen {
    void MainScreen::display() {
        std::cout << "Welcome!";
    }

    bool MainScreen::handleCommandInput(std::string input) {
        if (input == "menu") {
            Navigator::getInstance()->navigate(new MenuItemsScreen());
            return true;
        } else if (input == "orders") {
            Navigator::getInstance()->navigate(new OrdersListScreen());
            return true;
        }
        return false;
    }

    std::vector<Command *> *MainScreen::getCommands() {
        auto commands = Screen::getCommands();

        commands->push_back(new Command(new std::string("Review menu items [menu]")));
        commands->push_back(new Command(new std::string("Review orders [orders]")));
        return commands;
    }

    std::string MainScreen::getName() {
        return "Main screen";
    }
}
