#ifndef RESTARAUNT_ORDER_SERVICE_H
#define RESTARAUNT_ORDER_SERVICE_H

#include "../model/order.h"

using namespace model;

namespace service {

    class OrderService {
    public:
        static OrderService *getInstance();
        unsigned int getOrderTotalPrice(Order *order);

    private:
        static OrderService *instance;
    };
}

#endif
