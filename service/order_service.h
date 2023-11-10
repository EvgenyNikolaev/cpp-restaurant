#ifndef RESTARAUNT_ORDER_SERVICE_H
#define RESTARAUNT_ORDER_SERVICE_H

#include "../model/order.h"
#include <string>
#include <vector>

using namespace model;

namespace service {

    class OrderService {
    public:
        static OrderService *getInstance();

        unsigned int getOrderTotalPrice(Order *order);

        std::vector<Order *> *search(std::vector<Order *> *orders, std::string *searchBy);

        std::vector<Order *> *filterNotServed(std::vector<Order *> *orders);

    private:
        static OrderService *instance;
    };
}

#endif
