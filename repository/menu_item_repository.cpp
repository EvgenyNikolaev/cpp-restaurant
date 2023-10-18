#include "menu_item_repository.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace repository {
    MenuItemRepository *MenuItemRepository::instance;

    MenuItemRepository *MenuItemRepository::getInstance() {
        if (instance == nullptr) {
            instance = new MenuItemRepository();
        }
        return instance;
    }

    std::vector<MenuItem *> *MenuItemRepository::getAll() {
        return menuItems;
    }

    MenuItemRepository::MenuItemRepository() {
        menuItems = new std::vector<MenuItem *>();
        load();
    }

    void MenuItemRepository::store() {
        std::ofstream newFile("menuItems.bin", std::ios::binary);
        newFile.write((char *) &idAutoincrement, sizeof (unsigned long int));
        for (auto menuItem: *menuItems) {
            newFile.write((char *) menuItem, sizeof(MenuItem));
        }

        newFile.close();
    }

    void MenuItemRepository::load() {
        if (!std::filesystem::exists("menuItems.bin")) {
            return;
        }

        std::ifstream file("menuItems.bin", std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error opening file." << std::endl;
        }

        if (file.read((char *) &idAutoincrement, sizeof (unsigned long int))) {
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
}

