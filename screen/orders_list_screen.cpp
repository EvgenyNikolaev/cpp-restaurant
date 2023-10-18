#include "../repository/order_repository.h"
#include "orders_list_screen.h"
#include "create_order_screen.h"
#include <iostream>

using namespace repository;

namespace screen {
    void OrdersListScreen::display() {
        std::cout << "Orders list\n";

        auto orders = OrderRepository::getInstance()->getAll();
        printOrdersList(orders);
    }

    std::vector<Command *> *OrdersListScreen::getCommands() {
        auto commands = new std::vector<Command *>();
        commands->push_back(new Command((std::string *) "Add order (add)"));
        commands->push_back(new Command((std::string *) "View order (view <id>)"));
        return commands;
    }

    void OrdersListScreen::printOrdersList(std::vector<Order *> *orders) {
        for (const Order *order: *orders) {
            std::cout << printf("|%5lu|%12s|%3s|%8s|",
                                order->id,
                                std::asctime(&order->createdAt),
                                order->isPaid ? "yes" : "no",
                                order->table);

        }
    }

    bool OrdersListScreen::handleCommandInput(std::string input) {
        bool handled = false;
        if (input == "add") {
            Navigator::getInstance()->navigate(new CreateOrderScreen());
            handled = true;
        }

        return handled;
    }

    std::string OrdersListScreen::getName() {
        return std::string("Orders");
    }
}
