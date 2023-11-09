#include "order_menu_item_repository.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace repository {
    OrderMenuItemRepository *OrderMenuItemRepository::instance;

    OrderMenuItemRepository *OrderMenuItemRepository::getInstance() {
        if (instance == nullptr) {
            instance = new OrderMenuItemRepository();
        }
        return instance;
    }

    OrderMenuItemRepository::OrderMenuItemRepository() {
        orderMenuItems = new std::vector<OrderMenuItem *>();
        load();
    }

    void OrderMenuItemRepository::store() {
        std::ofstream file("orderMenuItems.bin", std::ios::binary);
        file.write((char *) &idAutoincrement, sizeof(unsigned long int));
        for (auto orderMenuItem: *orderMenuItems) {
            file.write((char *) orderMenuItem, sizeof(OrderMenuItem));
        }

        file.close();
    }

    void OrderMenuItemRepository::load() {
        if (!std::filesystem::exists("orderMenuItems.bin")) {
            return;
        }

        std::ifstream file("orderMenuItems.bin", std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error opening file." << std::endl;
        }

        if (file.read((char *) &idAutoincrement, sizeof(unsigned long int))) {
            auto orderMenuItem = new OrderMenuItem();
            while (file.read((char *) orderMenuItem, sizeof(OrderMenuItem))) {
                orderMenuItems->push_back(orderMenuItem);
                orderMenuItem = new OrderMenuItem();
            }
        }

        file.close();
    }

    void OrderMenuItemRepository::add(OrderMenuItem *orderMenuItem) {
        orderMenuItem->id = ++idAutoincrement;
        orderMenuItems->push_back(orderMenuItem);
        store();
    }

    OrderMenuItem *OrderMenuItemRepository::getById(unsigned long id) {
        for (auto &orderMenuItem: *orderMenuItems) {
            if (orderMenuItem->id == id) {
                return orderMenuItem;
            }
        }

        return nullptr;
    }

    std::vector<OrderMenuItem *> *OrderMenuItemRepository::getByOrderId(unsigned long orderId) {
        auto filteredVector = new std::vector<OrderMenuItem *>();
        for (auto orderMenuItem: *orderMenuItems) {
            if (orderMenuItem->orderId == orderId) {
                filteredVector->push_back(orderMenuItem);
            }
        }
        return filteredVector;
    }

    bool OrderMenuItemRepository::deleteById(unsigned long id) {
        for (auto i = 0; i < orderMenuItems->size(); i++) {
            if (orderMenuItems->at(i)->id == id) {
                orderMenuItems->erase(orderMenuItems->begin() + i);
                store();
                return true;
            }
        }

        return false;
    }

}

