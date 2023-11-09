#include "../repository/order_repository.h"
#include "../repository/order_menu_item_repository.h"
#include "../repository/menu_item_repository.h"
#include "orders_list_screen.h"
#include "order_screen.h"
#include "../helper/view_helper.h"
#include "../service/order_service.h"
#include <iostream>
#include <string>
#include <vector>

using namespace repository;
using namespace helper;

namespace screen {
    void OrdersListScreen::display() {

        if (searchBy != nullptr && searchBy->length() > 0) {
            std::cout << "Search by: " << searchBy->c_str() << std::endl;
        }

        printOrdersList();
    }

    std::vector<Command *> *OrdersListScreen::getCommands() {
        auto commands = new std::vector<Command *>();
        commands->push_back(new Command(new std::string("New order [new]")));
        commands->push_back(new Command(new std::string("View order [view]")));
        commands->push_back(new Command(new std::string("Filter [filter]")));
        commands->push_back(new Command(new std::string("Search [search]")));
        commands->push_back(new Command(new std::string("Reset [reset]")));
        return commands;
    }

    void OrdersListScreen::printOrdersList() {

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
        } else if (input == "search") {
            search();
            return true;
        } else if (input == "reset") {
            reset();
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

    OrdersListScreen::OrdersListScreen(std::vector<Order *> *orders, std::string *searchBy) {
        this->orders = orders;
        this->searchBy = searchBy;
    }

    void OrdersListScreen::search() {

        std::string searchTerm;
        std::cout << "Search string: ";
        std::cin >> searchTerm;

        auto filteredOrders = OrderService::getInstance()->search(&searchTerm);
        Navigator::getInstance()->navigate(new OrdersListScreen(filteredOrders, &searchTerm), true);
    }

    void OrdersListScreen::reset() {
        auto allOrders = OrderRepository::getInstance()->getAll();
        Navigator::getInstance()->navigate(new OrdersListScreen(allOrders, nullptr), true);
    }
}
