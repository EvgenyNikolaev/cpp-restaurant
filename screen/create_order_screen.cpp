#include <cstring>
#include "create_order_screen.h"
#include "../repository/order_repository.h"
#include "../model/order.h"

using namespace model;
using namespace repository;
using namespace service;

namespace screen {
    void CreateOrderScreen::display() {
        auto orders = OrderRepository::getInstance()->getAll();

        // TODO: change with promtps
        auto order = new Order();
        order->id = 1;
        order->isPaid = true;
        strcpy(order->table, "A");
        std::time_t t = std::time(nullptr);
        order->createdAt = *std::localtime(&t);
        orders->push_back(order);

        OrderRepository::getInstance()->store();
    }

    std::vector<Command *> *CreateOrderScreen::getCommands() {
        return Screen::getCommands();
    }

    bool CreateOrderScreen::handleCommandInput(std::string input) {
        return false;
    }

    std::string CreateOrderScreen::getName() {
        return std::string("Ceate order");
    }
}