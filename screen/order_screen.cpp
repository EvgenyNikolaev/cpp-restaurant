#include <cstring>
#include <iostream>
#include "order_screen.h"
#include "../repository/order_menu_item_repository.h"
#include "../repository/menu_item_repository.h"
#include "../model/order.h"
#include "../helper/view_helper.h"
#include "../service/order_service.h"

using namespace model;
using namespace repository;
using namespace service;
using namespace helper;

namespace screen {
    void OrderScreen::display() {

        auto totalPrice = ViewHelper::formatPrice(OrderService::getInstance()->getOrderTotalPrice(order));
        ViewHelper::printProperty("Order id", std::to_string(order->id));
        ViewHelper::printProperty("Table", order->table);
        ViewHelper::printProperty("Total", totalPrice);
        printOrderMenuItems();
    }

    std::vector<Command *> *OrderScreen::getCommands() {
        auto commands = new std::vector<Command *>();
        commands->push_back(new Command(new std::string("Add item [add]")));
        commands->push_back(new Command(new std::string("Remove item [remove]")));
        commands->push_back(new Command(new std::string("Mark served [serve]")));
        return commands;
    }

    bool OrderScreen::handleCommandInput(std::string input) {
        if (input == "add") {
            addOrderMenuItem();
            return true;
        } else if (input == "remove") {
            deleteOrderMenuItem();
            return true;
        } else if (input == "serve") {
            markOrderMenuItemServed();
            return true;
        }

        return false;
    }

    std::string OrderScreen::getName() {
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
        int userInput;

        std::cout << "Select menu item from the list above: " << std::endl;
        while (menuItem == nullptr) {
            std::cin >> userInput;
            menuItem = MenuItemRepository::getInstance()->getById(userInput);
            std::cout << "Please try again: ";
        }

        orderMenuItem->menuItemId = menuItem->id;
        orderMenuItem->isServed = false;

        std::cout << "Qty: ";
        std::cin >> orderMenuItem->qty;

        OrderMenuItemRepository::getInstance()->add(orderMenuItem);
        Navigator::getInstance()->navigate(new OrderScreen(order), true);
    }

    void OrderScreen::deleteOrderMenuItem() {
        unsigned long int id;

        std::cout << "Id: ";
        std::cin >> id;

        if (OrderMenuItemRepository::getInstance()->deleteById(id)) {
            Navigator::getInstance()->navigate(new OrderScreen(order), true);
        } else {
            std::cout << "Failed to delete. Please try again." << std::endl;
            deleteOrderMenuItem();
        }
    }

    void OrderScreen::markOrderMenuItemServed() {
        unsigned long int id;

        std::cout << "Id: ";
        std::cin >> id;

        auto orderMenuItem = OrderMenuItemRepository::getInstance()->getById(id);
        if (orderMenuItem == nullptr) {
            std::cout << "Wrong id. Please try again." << std::endl;
            markOrderMenuItemServed();
            return;
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