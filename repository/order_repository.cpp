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
        std::ofstream outputFile("orders.bin", std::ios::binary);
        outputFile.write((char *) &idAutoincrement, 32);
        for (auto order: *orders) {
            outputFile.write((char *) order, sizeof(Order));
        }

        outputFile.close();
    }

    void OrderRepository::load() {
        if (!std::filesystem::exists("orders.bin")) {
            return;
        }

        std::ifstream file("orders.bin", std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error opening file." << std::endl;
        }

        if (file.read((char *) &idAutoincrement, 32)) {
            Order *order;
            while (file.read((char *) order, sizeof(Order))) {
                orders->push_back(order);
            }
        }

        file.close();
    }

    void OrderRepository::add(Order *order) {
        order->id = ++idAutoincrement;
        orders->push_back(order);
        store();
    }
}

