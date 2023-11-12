#ifndef RESTARAUNT_SCREENS_ORDERS_H
#define RESTARAUNT_SCREENS_ORDERS_H

#include <string>
#include "../service/navigation.h"
#include "../repository/order_repository.h"
#include "../service/order_service.h"

using namespace service;

namespace screen {
    class OrdersListScreen : public Screen {
    public:
        explicit OrdersListScreen(std::string *searchBy = nullptr,
                                  FilterOption *filterBy = nullptr,
                                  SortOption *sortBy = nullptr);

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

        void sort();

        void setupList();

        std::vector<Order *> *orders;
        std::string *searchBy = nullptr;
        FilterOption *filterBy = nullptr;
        SortOption *sortBy = nullptr;
    };
}

#endif
