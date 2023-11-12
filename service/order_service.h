#ifndef RESTARAUNT_ORDER_SERVICE_H
#define RESTARAUNT_ORDER_SERVICE_H

#include "../model/order.h"
#include <string>
#include <vector>

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
        std::string getDescription(Order *order);

        std::vector<Order *> *search(std::vector<Order *> *orders, std::string *searchBy);

        std::vector<Order *> *filter(std::vector<Order *> *orders, FilterOption *filterOptions);

        std::vector<Order *> *sort(std::vector<Order *> *orders, SortOption *sortOptions);

    private:
        static OrderService *instance;
    };
}

#endif
