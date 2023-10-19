#ifndef RESTARAUNT_ORDER_REPOSITORY_H
#define RESTARAUNT_ORDER_REPOSITORY_H

#include <vector>
#include <fstream>
#include "../model/order.h"

using namespace model;

namespace repository {
    class OrderRepository {
    private:
        static OrderRepository *instance;
        std::vector<Order *> *orders;

        void load();

        unsigned long int idAutoincrement = 0;

    public:
        OrderRepository();

        static OrderRepository *getInstance();

        std::vector<Order *> *getAll();

        void add(Order *order);

        void store();

        Order *getById(unsigned long int id);

    };
}


#endif
