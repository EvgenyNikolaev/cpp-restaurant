#ifndef RESTARAUNT_ORDER_SERVICE_H
#define RESTARAUNT_ORDER_SERVICE_H

#include "../model/order.h"
#include <string>
#include <vector>

using namespace std;
using namespace model;

namespace service {

    enum SortOption {
        TOTAL_PRICE_ASC
    };

    enum FilterOption {
        NOT_SERVED
    };

    class OrderService {
    public:
        static OrderService *getInstance();

        unsigned int getOrderTotalPrice(Order *order);

        bool getIsFullyServed(Order *order);
        string getDescription(Order *order);

        vector<Order *> *search(vector<Order *> *orders, string *searchBy);

        vector<Order *> *filter(vector<Order *> *orders, FilterOption *filterOptions);

        vector<Order *> *sort(vector<Order *> *orders, SortOption *sortOptions);

    private:
        static OrderService *instance;
    };
}

#endif
