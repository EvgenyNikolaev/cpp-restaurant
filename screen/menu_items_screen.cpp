#include "menu_items_screen.h"
#include "../repository/menu_item_repository.h"
#include "../helper/view_helper.h"
#include <iostream>

using namespace service;
using namespace repository;
using namespace model;
using namespace helper;

namespace screen {
    void MenuItemsScreen::display() {
        printList();
    }

    bool MenuItemsScreen::handleCommandInput(string input) {
        if (input == COMMAND_ADD) {
            addMenuItem();
            return true;
        } else if (input == COMMAND_EDIT) {
            editMenuItem();
            return true;
        } else if (input == COMMAND_DELETE) {
            deleteMenuItem();
            return true;
        }
        return false;
    }

    vector<Command *> *MenuItemsScreen::getCommands() {
        auto commands = Screen::getCommands();

        commands->push_back(new Command(&COMMAND_ADD, new string("Add")));
        commands->push_back(new Command(&COMMAND_EDIT, new string("Edit")));
        commands->push_back(new Command(&COMMAND_DELETE, new string("Delete")));
        return commands;
    }

    void MenuItemsScreen::printList() {

        printf("|%8s|%100s|%8s|", "id", "name", "price");
        ViewHelper::printHorizontalRule();
        auto menuItems = MenuItemRepository::getInstance()->getAll();
        for (auto menuItem: *menuItems) {
            printf("|%8lu|%100s|%8s|\n", menuItem->id, menuItem->name,
                   ViewHelper::formatPrice(menuItem->priceInCents).c_str());
        }
    }

    void MenuItemsScreen::addMenuItem() {
        auto menuItem = new MenuItem();

        cout << "Name: ";
        cin.ignore();
        cin.getline(menuItem->name, 32);

        ViewHelper::integerInput("Price in cents", &menuItem->priceInCents);

        MenuItemRepository::getInstance()->add(menuItem);
        Navigator::getInstance()->navigate(new MenuItemsScreen(), true);
    }

    void MenuItemsScreen::deleteMenuItem() {

        unsigned int userInput;
        bool deleted = false;
        while (!deleted) {
            ViewHelper::integerInput("Select menu item ID from the list above", &userInput);
            deleted = MenuItemRepository::getInstance()->deleteById(userInput);
            if (deleted) {
                Navigator::getInstance()->navigate(new MenuItemsScreen(), true);
            } else {
                cout << "Wrong ID" << endl;
            }
        }
    }

    string MenuItemsScreen::getName() {
        return "Menu items";
    }

    void MenuItemsScreen::editMenuItem() {

        unsigned int userInput;
        MenuItem *menuItem = nullptr;
        while (menuItem == nullptr) {
            ViewHelper::integerInput("Type in ID from the table", &userInput);
            menuItem = MenuItemRepository::getInstance()->getById(userInput);
            if (menuItem == nullptr) {
                cout << "Wrong ID" << endl;
            }
        }

        cout << "Name (" << menuItem->name << "): ";
        cin.ignore();
        cin.getline(menuItem->name, 32);
        cout << endl;

        ViewHelper::integerInput("Price (" + to_string(menuItem->priceInCents) + ")", &menuItem->priceInCents);

        MenuItemRepository::getInstance()->store();
        Navigator::getInstance()->navigate(new MenuItemsScreen(), true);
    }
}
