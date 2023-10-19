#ifndef RESTARAUNT_SCREENS_ORDERS_H
#define RESTARAUNT_SCREENS_ORDERS_H

#include <string>
#include "../service/navigation.h"
#include "../repository/order_repository.h"

using namespace service;

namespace screen {
    class OrdersListScreen : public Screen {
    public:

        void display() override;

        std::vector<Command *> *getCommands() override;

        bool handleCommandInput(std::string input) override;

        std::string getName() override;

    private:

        static void printOrdersList(std::vector<Order *> *pVector);

        void createNewOrder();

        void viewOrder();
    };
}

#endif
