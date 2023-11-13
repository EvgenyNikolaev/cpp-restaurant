#include <iostream>
#include "order_screen.h"
#include "../repository/order_menu_item_repository.h"
#include "../repository/menu_item_repository.h"
#include "../helper/view_helper.h"
#include "../service/order_service.h"

using namespace std;
using namespace model;
using namespace repository;
using namespace service;
using namespace helper;

namespace screen {
    void OrderScreen::display() {

        auto totalPrice = ViewHelper::formatPrice(OrderService::getInstance()->getOrderTotalPrice(order));
        ViewHelper::printProperty("Order id", to_string(order->id));
        ViewHelper::printProperty("Table", order->table);
        ViewHelper::printProperty("Total", totalPrice);
        printOrderMenuItems();
    }

    vector<Command *> *OrderScreen::getCommands() {
        auto commands = new vector<Command *>();
        commands->push_back(new Command(&COMMAND_ADD, new string("Add item")));
        commands->push_back(new Command(&COMMAND_REMOVE, new string("Remove item")));
        commands->push_back(new Command(&COMMAND_SERVE, new string("Mark served")));
        return commands;
    }

    bool OrderScreen::handleCommandInput(string input) {
        if (input == COMMAND_ADD) {
            addOrderMenuItem();
            return true;
        } else if (input == COMMAND_REMOVE) {
            deleteOrderMenuItem();
            return true;
        } else if (input == COMMAND_SERVE) {
            markOrderMenuItemServed();
            return true;
        }

        return false;
    }

    string OrderScreen::getName() {
        return "Order details";
    }

    OrderScreen::OrderScreen(Order *order) : order(order) {

    }

    void OrderScreen::printOrderMenuItems() {
        ViewHelper::printHorizontalRule();

        auto orderMenuItems = OrderMenuItemRepository::getInstance()->getByOrderId(order->id);
        printf("|%5s|%79s|%12s|%12s|%6s|\n", "id", "name", "qty", "price", "served");
        for (auto orderMenuItem: *orderMenuItems) {
            auto menuItem = MenuItemRepository::getInstance()->getById(orderMenuItem->menuItemId);

            printf("|%5lu|%79s|%12u|%12s|%6s|\n", orderMenuItem->id, menuItem->name,
                   orderMenuItem->qty, ViewHelper::formatPrice(menuItem->priceInCents).c_str(),
                   orderMenuItem->isServed ? "yes" : "no");
        }
    }

    void OrderScreen::addOrderMenuItem() {
        auto orderMenuItem = new OrderMenuItem();
        orderMenuItem->orderId = order->id;

        printMenuItemsOptions();

        MenuItem *menuItem = nullptr;
        unsigned int userInput;

        while (menuItem == nullptr) {
            ViewHelper::integerInput("Select menu item ID from the list above", &userInput);
            menuItem = MenuItemRepository::getInstance()->getById(userInput);
            if (menuItem == nullptr) {
                cout << "Wrong ID" << endl;
            }
        }

        orderMenuItem->menuItemId = menuItem->id;
        orderMenuItem->isServed = false;

        ViewHelper::integerInput("Qty", &orderMenuItem->qty);

        OrderMenuItemRepository::getInstance()->add(orderMenuItem);
        Navigator::getInstance()->navigate(new OrderScreen(order), true);
    }

    void OrderScreen::deleteOrderMenuItem() {

        unsigned int userInput;
        bool deleted = false;
        while (!deleted) {
            ViewHelper::integerInput("Select menu item ID from the list above", &userInput);
            deleted = OrderMenuItemRepository::getInstance()->deleteById(userInput);
            if (deleted) {
                Navigator::getInstance()->navigate(new OrderScreen(order), true);
            } else {
                cout << "Wrong ID" << endl;
            }
        }
    }

    void OrderScreen::markOrderMenuItemServed() {

        unsigned int userInput;
        OrderMenuItem *orderMenuItem = nullptr;
        while (orderMenuItem == nullptr) {
            ViewHelper::integerInput("Type in ID from the table", &userInput);
            orderMenuItem = OrderMenuItemRepository::getInstance()->getById(userInput);
            if (orderMenuItem == nullptr) {
                cout << "Wrong ID" << endl;
            }
        }

        orderMenuItem->isServed = true;
        OrderMenuItemRepository::getInstance()->store();
        Navigator::getInstance()->navigate(new OrderScreen(order), true);
    }

    void OrderScreen::printMenuItemsOptions() {

        auto menuItems = MenuItemRepository::getInstance()->getAll();
        printf("%4s%32s\n", "id", "name");
        for (auto menuItem: *menuItems) {
            printf("%4lu%32s\n", menuItem->id, menuItem->name);
        }
    }
}