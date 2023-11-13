#include "menu_item_repository.h"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

namespace repository {
    MenuItemRepository *MenuItemRepository::instance;

    MenuItemRepository *MenuItemRepository::getInstance() {
        if (instance == nullptr) {
            instance = new MenuItemRepository();
        }
        return instance;
    }

    vector<MenuItem *> *MenuItemRepository::getAll() {
        return menuItems;
    }

    MenuItemRepository::MenuItemRepository() {
        menuItems = new vector<MenuItem *>();
        load();
    }

    void MenuItemRepository::store() {
        ofstream file("menuItems.bin", ios::binary);
        file.write((char *) &idAutoincrement, sizeof(unsigned long int));
        for (auto menuItem: *menuItems) {
            file.write((char *) menuItem, sizeof(MenuItem));
        }

        file.close();
    }

    void MenuItemRepository::load() {
        if (!filesystem::exists("menuItems.bin")) {
            return;
        }

        ifstream file("menuItems.bin", ios::binary);
        if (!file.is_open()) {
            cerr << "Error opening file." << endl;
        }

        if (file.read((char *) &idAutoincrement, sizeof(unsigned long int))) {
            auto menuItem = new MenuItem();
            while (file.read((char *) menuItem, sizeof(MenuItem))) {
                menuItems->push_back(menuItem);
                menuItem = new MenuItem();
            }
        }

        file.close();
    }

    void MenuItemRepository::add(MenuItem *menuItem) {
        menuItem->id = ++idAutoincrement;
        menuItems->push_back(menuItem);
        store();
    }

    bool MenuItemRepository::deleteById(unsigned long id) {

        for (auto i = 0; i < menuItems->size(); i++) {
            if (menuItems->at(i)->id == id) {
                menuItems->erase(menuItems->begin() + i);
                store();
                return true;
            }
        }

        return false;
    }

    MenuItem *MenuItemRepository::getById(unsigned long id) {
        for (auto &menuItem: *menuItems) {
            if (menuItem->id == id) {
                return menuItem;
            }
        }

        return nullptr;
    }
}

