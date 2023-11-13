#ifndef RESTARAUNT_MENUITEM_REPOSITORY_H
#define RESTARAUNT_MENUITEM_REPOSITORY_H

#include <vector>
#include <fstream>
#include "../model/menu_item.h"

using namespace model;
using namespace std;

namespace repository {
    class MenuItemRepository {
    private:
        static MenuItemRepository *instance;
        vector<MenuItem *> *menuItems;

        void load();

        unsigned long int idAutoincrement = 0;

    public:
        MenuItemRepository();

        static MenuItemRepository *getInstance();

        vector<MenuItem *> *getAll();

        void add(MenuItem *menuItem);

        bool deleteById(unsigned long int id);

        MenuItem *getById(unsigned long int id);

        void store();
    };
}


#endif
