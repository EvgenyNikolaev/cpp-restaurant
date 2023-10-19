#include "order_repository.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace repository {
    OrderRepository *OrderRepository::instance;

    OrderRepository *OrderRepository::getInstance() {
        if (instance == nullptr) {
            instance = new OrderRepository();
        }
        return instance;
    }

    std::vector<Order *> *OrderRepository::getAll() {
        return orders;
    }

    OrderRepository::OrderRepository() {
        orders = new std::vector<Order *>();
        load();
    }

    void OrderRepository::store() {
        std::ofstream file("orders.bin", std::ios::binary);
        file.write((char *) &idAutoincrement, sizeof(unsigned long int));
        for (auto order: *orders) {
            file.write((char *) order, sizeof(Order));
        }

        file.close();
    }

    void OrderRepository::load() {
        if (!std::filesystem::exists("orders.bin")) {
            return;
        }

        std::ifstream file("orders.bin", std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error opening file." << std::endl;
        }

        if (file.read((char *) &idAutoincrement, sizeof(unsigned long int))) {
            auto order = new Order();
            while (file.read((char *) order, sizeof(Order))) {
                orders->push_back(order);
                order = new Order();
            }
        }

        file.close();
    }

    void OrderRepository::add(Order *order) {
        order->id = ++idAutoincrement;
        std::time_t t = std::time(nullptr);
        order->createdAt = *std::localtime(&t);
        orders->push_back(order);
        store();
    }

    Order *OrderRepository::getById(unsigned long id) {
        for (auto &order: *orders) {
            if (order->id == id) {
                return order;
            }
        }

        return nullptr;
    }

}

