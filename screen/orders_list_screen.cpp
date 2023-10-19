#include "../repository/order_repository.h"
#include "orders_list_screen.h"
#include "order_screen.h"
#include "../helper/view_helper.h"
#include <iostream>

using namespace repository;
using namespace helper;

namespace screen {
    void OrdersListScreen::display() {
        auto orders = OrderRepository::getInstance()->getAll();
        printOrdersList(orders);
    }

    std::vector<Command *> *OrdersListScreen::getCommands() {
        auto commands = new std::vector<Command *>();
        commands->push_back(new Command(new std::string("New order [new]")));
        commands->push_back(new Command(new std::string("View order [view]")));
        return commands;
    }

    void OrdersListScreen::printOrdersList(std::vector<Order *> *orders) {

        printf("|%5s|%12s|%30s|%6s|", "id", "table", "created at", "paid");
        ViewHelper::printHorizontalRule();
        for (const Order *order: *orders) {
            std::string createdAt = std::asctime(&order->createdAt);
            createdAt.pop_back();
            printf("|%5lu|%12s|%30s|%6s|\n", order->id, order->table, createdAt.c_str(),
                   order->isPaid ? "yes" : "no");
        }
    }

    bool OrdersListScreen::handleCommandInput(std::string input) {
        if (input == "new") {
            createNewOrder();
            return true;
        } else if (input == "view") {
            viewOrder();
            return true;
        }

        return false;
    }

    std::string OrdersListScreen::getName() {
        return "Orders";
    }

    void OrdersListScreen::createNewOrder() {
        auto order = new Order();

        std::cout << "Table: ";
        std::cin >> order->table;

        OrderRepository::getInstance()->add(order);
        Navigator::getInstance()->navigate(new OrderScreen(order));
    }

    void OrdersListScreen::viewOrder() {
        unsigned long int id;

        std::cout << "Id: ";
        std::cin >> id;

        auto order = OrderRepository::getInstance()->getById(id);
        if (order == nullptr) {
            std::cout << "Wrong id. Please try again." << std::endl;
            viewOrder();
            return;
        }
        Navigator::getInstance()->navigate(new OrderScreen(order));
    }
}
