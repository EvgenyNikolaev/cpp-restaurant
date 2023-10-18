#ifndef RESTARAUNT_ORDER_MENU_ITEM_H
#define RESTARAUNT_ORDER_MENU_ITEM_H

namespace model {
    struct OrderMenuItem {
        unsigned long int id;
        unsigned long int orderId;
        unsigned long int menuItemId;
        unsigned int qty;
        bool isServed;
    };
}


#endif
