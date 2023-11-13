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

    bool MenuItemsScreen::handleCommandInput(std::string input) {
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

    std::vector<Command *> *MenuItemsScreen::getCommands() {
        auto commands = Screen::getCommands();

        commands->push_back(new Command(&COMMAND_ADD, new std::string("Add")));
        commands->push_back(new Command(&COMMAND_EDIT, new std::string("Edit")));
        commands->push_back(new Command(&COMMAND_DELETE, new std::string("Delete")));
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

        std::cout << "Name: ";
        std::cin.ignore();
        std::cin.getline(menuItem->name, 32);

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
        return "Menu items";
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
        std::cin.ignore();
        std::cin.getline(menuItem->name, 32);
        std::cout << std::endl;

        std::cout << "Price (" << menuItem->priceInCents << "): ";
        std::cin >> menuItem->priceInCents;
        std::cout << std::endl;

        MenuItemRepository::getInstance()->store();
        Navigator::getInstance()->navigate(new MenuItemsScreen(), true);
    }
}
