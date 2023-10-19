#include <cstring>
#include <iostream>
#include "order_screen.h"
#include "../repository/order_repository.h"
#include "../model/order.h"
#include "../helper/view_helper.h"

using namespace model;
using namespace repository;
using namespace service;
using namespace helper;

namespace screen {
    void OrderScreen::display() {

        std::cout << "Order id: " << order->id << std::endl;
        std::cout << "Table: " << order->table << std::endl;
        ViewHelper::printHorizontalRule();
    }

    std::vector<Command *> *OrderScreen::getCommands() {
        return Screen::getCommands();
    }

    bool OrderScreen::handleCommandInput(std::string input) {
        return false;
    }

    std::string OrderScreen::getName() {
        return "Order";
    }

    OrderScreen::OrderScreen(Order *order) : order(order) {

    }
}