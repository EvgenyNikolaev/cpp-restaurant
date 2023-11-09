#ifndef RESTARAUNT_ORDERMENUITEM_REPOSITORY_H
#define RESTARAUNT_ORDERMENUITEM_REPOSITORY_H

#include <vector>
#include <fstream>
#include "../model/order_menu_item.h"

using namespace model;

namespace repository {
    class OrderMenuItemRepository {
    private:
        static OrderMenuItemRepository *instance;
        std::vector<OrderMenuItem *> *orderMenuItems;

        void load();

        unsigned long int idAutoincrement = 0;

    public:
        OrderMenuItemRepository();

        static OrderMenuItemRepository *getInstance();

        std::vector<OrderMenuItem *> *getByOrderId(unsigned long int orderId);

        void add(OrderMenuItem *orderMenuItem);

        void store();

        OrderMenuItem *getById(unsigned long int id);

        bool deleteById(unsigned long int id);



    };
}


#endif
