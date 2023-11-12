#include "../repository/order_repository.h"
#include "orders_list_screen.h"
#include "order_screen.h"
#include "../helper/view_helper.h"
#include <iostream>
#include <string>
#include <vector>

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
            std::string filters;
            if (*filterBy == FilterOption::NOT_SERVED) {
                filters = "Not served";
            }
            ViewHelper::printProperty("Filter by", filters);
            printHr = true;
        }
        if (sortBy != nullptr) {
            std::string sorting;
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

    std::vector<Command *> *OrdersListScreen::getCommands() {
        auto commands = new std::vector<Command *>();
        commands->push_back(new Command(new std::string("New order [new]")));
        commands->push_back(new Command(new std::string("View order [view]")));
        commands->push_back(new Command(new std::string("Filter [filter]")));
        commands->push_back(new Command(new std::string("Sort [sort]")));
        commands->push_back(new Command(new std::string("Search [search]")));
        commands->push_back(new Command(new std::string("Reset [reset]")));
        return commands;
    }

    void OrdersListScreen::printOrdersList() {

        printf("|%5s|%12s|%33s|%30s|%20s|%6s|%6s|", "id", "table", "description", "created at", "total", "served",
               "paid");
        ViewHelper::printHorizontalRule();
        for (auto order: *orders) {
            std::string createdAt = std::asctime(&order->createdAt);
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
        } else if (input == "filter") {
            filter();
            return true;
        } else if (input == "sort") {
            sort();
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

    OrdersListScreen::OrdersListScreen(std::string *searchBy, FilterOption *filterBy, SortOption *sortBy) {
        this->searchBy = searchBy;
        this->filterBy = filterBy;
        this->sortBy = sortBy;
        setupList();
    }

    void OrdersListScreen::search() {

        std::string newSearchBy;
        std::cout << "Search string: ";
        std::cin >> newSearchBy;

        Navigator::getInstance()
                ->navigate(new OrdersListScreen(&newSearchBy, this->filterBy), true);
    }

    void OrdersListScreen::reset() {
        Navigator::getInstance()->navigate(new OrdersListScreen(), true);
    }

    void OrdersListScreen::filter() {
        FilterOption filterOption;
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
        sortOption = SortOption::TOTAL_PRICE_ASC;

        Navigator::getInstance()->navigate(
                new OrdersListScreen(this->searchBy, this->filterBy, &sortOption), true);
    }
}
