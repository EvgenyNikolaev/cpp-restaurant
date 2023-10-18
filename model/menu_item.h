#ifndef RESTARAUNT_MENU_ITEM_H
#define RESTARAUNT_MENU_ITEM_H

namespace model {
    struct MenuItem {
        unsigned long int id;
        char name[32];
        unsigned int priceInCents;
    };
}


#endif
