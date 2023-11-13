#ifndef RESTARAUNT_SCREENS_ORDERS_H
#define RESTARAUNT_SCREENS_ORDERS_H

#include <string>
#include "../service/navigation.h"
#include "../repository/order_repository.h"
#include "../service/order_service.h"

using namespace std;
using namespace service;

namespace screen {
    class OrdersListScreen : public Screen {
    public:
        explicit OrdersListScreen(string *searchBy = nullptr,
                                  FilterOption *filterBy = nullptr,
                                  SortOption *sortBy = nullptr);

        void display() override;

        vector<Command *> *getCommands() override;

        bool handleCommandInput(string input) override;

        string getName() override;

    private:
        constexpr static const string COMMAND_NEW = "new";
        constexpr static const string COMMAND_VIEW = "view";
        constexpr static const string COMMAND_FILTER = "filter";
        constexpr static const string COMMAND_SORT = "sort";
        constexpr static const string COMMAND_SEARCH = "search";
        constexpr static const string COMMAND_RESET = "reset";


        void printOrdersList();

        void createNewOrder();

        void viewOrder();

        void search();

        void reset();

        void filter();

        void sort();

        void setupList();

        vector<Order *> *orders;
        string *searchBy = nullptr;
        FilterOption *filterBy = nullptr;
        SortOption *sortBy = nullptr;
    };
}

#endif
