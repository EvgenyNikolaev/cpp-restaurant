#ifndef RESTARAUNT_ORDER_SCREEN_H
#define RESTARAUNT_ORDER_SCREEN_H

#include "../service/navigation.h"
#include "../model/order.h"
#include "../model/menu_item.h"

using namespace service;
using namespace model;

namespace screen {

    class OrderScreen : public Screen {

    public:
        explicit OrderScreen(Order *order);

        void display() override;

        std::vector<Command *> *getCommands() override;

        bool handleCommandInput(std::string input) override;

        std::string getName() override;

    private:
        constexpr static const std::string COMMAND_ADD = "add";
        constexpr static const std::string COMMAND_REMOVE = "remove";
        constexpr static const std::string COMMAND_SERVE = "serve";

        Order *order = nullptr;

        void printOrderMenuItems();

        void addOrderMenuItem();

        void deleteOrderMenuItem();

        void markOrderMenuItemServed();

        void printMenuItemsOptions();
    };

}

#endif
