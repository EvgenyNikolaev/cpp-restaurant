#ifndef RESTARAUNT_SCREENS_ORDERS_H
#define RESTARAUNT_SCREENS_ORDERS_H

#include <string>
#include "../service/navigation.h"
#include "../repository/order_repository.h"

using namespace service;

namespace screen {
    class OrdersListScreen : public Screen {
    public:
        explicit OrdersListScreen(std::string *searchBy = nullptr, bool filterNotServed = false);

        void display() override;

        std::vector<Command *> *getCommands() override;

        bool handleCommandInput(std::string input) override;

        std::string getName() override;

    private:

        void printOrdersList();

        void createNewOrder();

        void viewOrder();

        void search();

        void reset();

        void filter();

        void setupList();

        std::vector<Order *> *orders;
        std::string *searchBy = nullptr;
        bool filterNotServed = false;
    };
}

#endif
