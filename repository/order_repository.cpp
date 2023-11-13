#include "order_repository.h"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

namespace repository {
    OrderRepository *OrderRepository::instance;

    OrderRepository *OrderRepository::getInstance() {
        if (instance == nullptr) {
            instance = new OrderRepository();
        }
        return instance;
    }

    vector<Order *> *OrderRepository::getAll() {
        return orders;
    }

    OrderRepository::OrderRepository() {
        orders = new vector<Order *>();
        load();
    }

    void OrderRepository::store() {
        ofstream file("orders.bin", ios::binary);
        file.write((char *) &idAutoincrement, sizeof(unsigned long int));
        for (auto order: *orders) {
            file.write((char *) order, sizeof(Order));
        }

        file.close();
    }

    void OrderRepository::load() {
        if (!filesystem::exists("orders.bin")) {
            return;
        }

        ifstream file("orders.bin", ios::binary);
        if (!file.is_open()) {
            cerr << "Error opening file." << endl;
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
        time_t t = time(nullptr);
        order->createdAt = *localtime(&t);
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

