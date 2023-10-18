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
            editMenuItem();
            return true;
        } else if (input == "delete") {
            deleteMenuItem();
            return true;
        }
        return false;
    }

    std::vector<Command *> *MenuItemsScreen::getCommands() {
        auto commands = Screen::getCommands();

        commands->push_back(new Command(new std::string("Add [add]")));
        commands->push_back(new Command(new std::string("Edit [edit]")));
        commands->push_back(new Command(new std::string("Delete [delete]")));
        return commands;
    }

    void MenuItemsScreen::printList() {
        auto menuItems = MenuItemRepository::getInstance()->getAll();
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
        Navigator::getInstance()->navigate(new MenuItemsScreen(), true);
    }

    void MenuItemsScreen::deleteMenuItem() {

        unsigned long int id;

        std::cout << "Id: ";
        std::cin >> id;

        if (MenuItemRepository::getInstance()->deleteById(id)) {
            Navigator::getInstance()->navigate(new MenuItemsScreen(), true);
        } else {
            std::cout << "Failed to delete. Please try again." << std::endl;
            deleteMenuItem();
        }

    }

    std::string MenuItemsScreen::getName() {
        return std::string("Menu items");
    }

    void MenuItemsScreen::editMenuItem() {
        unsigned long int id;

        std::cout << "Id: ";
        std::cin >> id;

        auto menuItem = MenuItemRepository::getInstance()->getById(id);
        if (menuItem == nullptr) {
            std::cout << "Wrong id. Please try again." << std::endl;
            editMenuItem();
            return;
        }

        std::cout << "Name (" << menuItem->name << "): ";
        std::cin >> menuItem->name;
        std::cout << std::endl;

        std::cout << "Price (" << menuItem->priceInCents << "): ";
        std::cin >> menuItem->priceInCents;
        std::cout << std::endl;

        MenuItemRepository::getInstance()->store();
        Navigator::getInstance()->navigate(new MenuItemsScreen(), true);
    }
}
