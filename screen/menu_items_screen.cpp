#include "menu_items_screen.h"
#include "../repository/menu_item_repository.h"
#include <iostream>

using namespace service;
using namespace repository;
using namespace model;

namespace screen {
    void MenuItemsScreen::display() {
        printList();
    }

    bool MenuItemsScreen::handleCommandInput(std::string input) {
        if (input == "add") {
            addMenuItem();
            return true;
        } else if (input == "edit") {
            // TODO
        } else if (input == "delete") {
            // TODO
        }
        return false;
    }

    std::vector<Command *> *MenuItemsScreen::getCommands() {
        auto commands = Screen::getCommands();

        commands->push_back(new Command(new std::string("Add [add]")));
        commands->push_back(new Command(new std::string("Edit [edit <id>]")));
        commands->push_back(new Command(new std::string("Delete [edit <id>]")));
        return commands;
    }

    void MenuItemsScreen::printList() {
        auto menuItems = MenuItemRepository::getInstance()->getAll();

        std::cout << std::endl;
        std::cout << "Menu items:\n";
        for (auto menuItem: *menuItems) {
            std::cout << printf("|%8lu|%32s|%8u|",
                                menuItem->id,
                                menuItem->name,
                                menuItem->priceInCents) << std::endl;

        }
    }

    void MenuItemsScreen::addMenuItem() {
        auto menuItem = new MenuItem();



        std::cout << "Name: ";
        std::cin >> menuItem->name;

        std::cout << "Price in cents: ";
        std::cin >> menuItem->priceInCents;

        MenuItemRepository::getInstance()->add(menuItem);
        Navigator::getInstance()->navigate(new MenuItemsScreen());
    }

    void MenuItemsScreen::deleteMenuItem() {

    }
}
