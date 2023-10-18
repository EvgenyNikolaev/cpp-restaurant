#ifndef RESTARAUNT_ORDER_H
#define RESTARAUNT_ORDER_H

#include <ctime>

namespace model {
    struct Order {
        unsigned long int id;
        char table[8];
        bool isPaid;
        tm createdAt;
        tm paidAt;
    };
}


#endif

