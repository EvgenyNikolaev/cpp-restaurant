#ifndef RESTARAUNT_ORDER_SCREEN_H
#define RESTARAUNT_ORDER_SCREEN_H

#include "../service/navigation.h"
#include "../model/order.h"

using namespace service;
using namespace model;

namespace screen {

    class OrderScreen : public Screen {
    public:
        OrderScreen(Order *order);

        void display() override;

        std::vector<Command *> *getCommands() override;

        bool handleCommandInput(std::string input) override;

        std::string getName() override;

    private:

        Order *order = nullptr;
    };

}

#endif
