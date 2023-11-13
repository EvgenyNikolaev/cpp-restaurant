#include "../repository/order_repository.h"
#include "orders_list_screen.h"
#include "order_screen.h"
#include "../helper/view_helper.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace repository;
using namespace helper;

namespace screen {
    void OrdersListScreen::display() {

        bool printHr = false;
        if (searchBy != nullptr && searchBy->length() > 0) {
            ViewHelper::printProperty("Search by", *searchBy);
            printHr = true;
        }
        if (filterBy != nullptr) {
            string filters;
            if (*filterBy == FilterOption::NOT_SERVED) {
                filters = "Not served";
            }
            ViewHelper::printProperty("Filter by", filters);
            printHr = true;
        }
        if (sortBy != nullptr) {
            string sorting;
            if (*sortBy == SortOption::TOTAL_PRICE_ASC) {
                sorting = "Total price (ASC)";
            }
            ViewHelper::printProperty("Sort by", sorting);
            printHr = true;
        }


        if (printHr) {
            ViewHelper::printHorizontalRule();
        }
        printOrdersList();
    }

    vector<Command *> *OrdersListScreen::getCommands() {
        auto commands = new vector<Command *>();
        commands->push_back(new Command(&COMMAND_NEW, new string("New order")));
        commands->push_back(new Command(&COMMAND_VIEW, new string("View order")));
        commands->push_back(new Command(&COMMAND_FILTER, new string("Filter")));
        commands->push_back(new Command(&COMMAND_SORT, new string("Sort")));
        commands->push_back(new Command(&COMMAND_SEARCH, new string("Search")));
        commands->push_back(new Command(&COMMAND_RESET, new string("Reset")));
        return commands;
    }

    void OrdersListScreen::printOrdersList() {

        printf("|%5s|%12s|%33s|%30s|%20s|%6s|%6s|", "id", "table", "description", "created at", "total", "served",
               "paid");
        ViewHelper::printHorizontalRule();
        for (auto order: *orders) {
            string createdAt = asctime(&order->createdAt);
            createdAt.pop_back();
            auto totalPrice = OrderService::getInstance()->getOrderTotalPrice(order);
            auto isFullyServed = OrderService::getInstance()->getIsFullyServed(order);
            auto description = OrderService::getInstance()->getDescription(order);
            printf("|%5lu|%12s|%33s|%30s|%20s|%6s|%6s|\n", order->id,
                   order->table,
                   description.c_str(),
                   createdAt.c_str(),
                   ViewHelper::formatPrice(totalPrice).c_str(),
                   isFullyServed ? "yes" : "no",
                   order->isPaid ? "yes" : "no");
        }
    }

    bool OrdersListScreen::handleCommandInput(string input) {
        if (input == COMMAND_NEW) {
            createNewOrder();
            return true;
        } else if (input == COMMAND_VIEW) {
            viewOrder();
            return true;
        } else if (input == COMMAND_SEARCH) {
            search();
            return true;
        } else if (input == COMMAND_RESET) {
            reset();
            return true;
        } else if (input == COMMAND_FILTER) {
            filter();
            return true;
        } else if (input == COMMAND_SORT) {
            sort();
            return true;
        }

        return false;
    }

    string OrdersListScreen::getName() {
        return "Orders";
    }

    void OrdersListScreen::createNewOrder() {
        auto order = new Order();

        cout << "Table: ";
        cin >> order->table;

        OrderRepository::getInstance()->add(order);
        Navigator::getInstance()->navigate(new OrderScreen(order));
    }

    void OrdersListScreen::viewOrder() {
        unsigned int userInput;
        Order *order = nullptr;
        while (order == nullptr) {
            ViewHelper::integerInput("Type in ID from the table", &userInput);
            order = OrderRepository::getInstance()->getById(userInput);
            if (order == nullptr) {
                cout << "Wrong ID" << endl;
            }
        }

        Navigator::getInstance()->navigate(new OrderScreen(order));
    }

    OrdersListScreen::OrdersListScreen(string *searchBy, FilterOption *filterBy, SortOption *sortBy) {
        this->searchBy = searchBy;
        this->filterBy = filterBy;
        this->sortBy = sortBy;
        setupList();
    }

    void OrdersListScreen::search() {

        string newSearchBy;
        cout << "Search string: ";
        getline(cin, newSearchBy);

        Navigator::getInstance()
                ->navigate(new OrdersListScreen(&newSearchBy, this->filterBy), true);
    }

    void OrdersListScreen::reset() {
        Navigator::getInstance()->navigate(new OrdersListScreen(), true);
    }

    void OrdersListScreen::filter() {
        FilterOption filterOption;
        string selectedOption;
        cout << "Selected filter by:\n";

        // At the moment only one options supported
        cout << "1) Not served:\n";
        cin >> selectedOption;

        if (selectedOption != "1") {
            cout << "Wrong option.\n";
            filter();
        }
        filterOption = FilterOption::NOT_SERVED;

        Navigator::getInstance()->navigate(
                new OrdersListScreen(this->searchBy, &filterOption, this->sortBy), true);
    }

    void OrdersListScreen::setupList() {
        orders = OrderRepository::getInstance()->getAll();
        if (this->filterBy != nullptr) {
            orders = OrderService::getInstance()->filter(orders, this->filterBy);
        }
        if (this->searchBy != nullptr) {
            orders = OrderService::getInstance()->search(orders, searchBy);
        }
        if (this->sortBy != nullptr) {
            orders = OrderService::getInstance()->sort(orders, this->sortBy);
        }
    }

    void OrdersListScreen::sort() {
        SortOption sortOption;
        string selectedOption;
        cout << "Selected sort by:\n";

        // At the moment only one options supported
        cout << "1) total price (ASC):\n";
        cin >> selectedOption;

        if (selectedOption != "1") {
            cout << "Wrong option.\n";
            filter();
        }
        sortOption = SortOption::TOTAL_PRICE_ASC;

        Navigator::getInstance()->navigate(
                new OrdersListScreen(this->searchBy, this->filterBy, &sortOption), true);
    }
}
