#ifndef RESTARAUNT_SCREENS_ORDERS_H
#define RESTARAUNT_SCREENS_ORDERS_H

#include <string>
#include "../service/navigation.h"
#include "../repository/order_repository.h"

using namespace service;

namespace screen {
    struct OrdersListScreen : Screen {

        void display() override;

        std::vector<Command *> *getCommands() override;

        bool handleCommandInput(std::string input) override;

        std::string getName() override;

        static void printOrdersList(std::vector<Order *> *pVector);
    };
}

#endif
