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

        cout << "Price in cents: ";
        cin >> menuItem->priceInCents;

        MenuItemRepository::getInstance()->add(menuItem);
        Navigator::getInstance()->navigate(new MenuItemsScreen(), true);
    }

    void MenuItemsScreen::deleteMenuItem() {

        unsigned long int id;

        cout << "Id: ";
        cin >> id;

        if (MenuItemRepository::getInstance()->deleteById(id)) {
            Navigator::getInstance()->navigate(new MenuItemsScreen(), true);
        } else {
            cout << "Failed to delete. Please try again." << endl;
            deleteMenuItem();
        }

    }

    string MenuItemsScreen::getName() {
        return "Menu items";
    }

    void MenuItemsScreen::editMenuItem() {
        unsigned long int id;

        cout << "Id: ";
        cin >> id;

        auto menuItem = MenuItemRepository::getInstance()->getById(id);
        if (menuItem == nullptr) {
            cout << "Wrong id. Please try again." << endl;
            editMenuItem();
            return;
        }

        cout << "Name (" << menuItem->name << "): ";
        cin.ignore();
        cin.getline(menuItem->name, 32);
        cout << endl;

        cout << "Price (" << menuItem->priceInCents << "): ";
        cin >> menuItem->priceInCents;
        cout << endl;

        MenuItemRepository::getInstance()->store();
        Navigator::getInstance()->navigate(new MenuItemsScreen(), true);
    }
}
