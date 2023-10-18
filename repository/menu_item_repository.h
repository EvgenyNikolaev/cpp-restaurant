#ifndef RESTARAUNT_MENUITEM_REPOSITORY_H
#define RESTARAUNT_MENUITEM_REPOSITORY_H

#include <vector>
#include <fstream>
#include "../model/menu_item.h"

using namespace model;

namespace repository {
    class MenuItemRepository {
    private:
        static MenuItemRepository *instance;
        std::vector<MenuItem *> *menuItems;

        void load();

        unsigned long int idAutoincrement = 0;

    public:
        MenuItemRepository();

        static MenuItemRepository *getInstance();

        std::vector<MenuItem *> *getAll();

        void add(MenuItem *menuItem);

        void store();
    };
}


#endif
