#include "order_service.h"
#include "../repository/order_menu_item_repository.h"
#include "../repository/menu_item_repository.h"

using namespace std;
using namespace repository;
using namespace model;

namespace service {
    OrderService *OrderService::instance = nullptr;

    OrderService *OrderService::getInstance() {
        if (instance == nullptr) {
            instance = new OrderService();
        }
        return instance;
    }

    unsigned int OrderService::getOrderTotalPrice(Order *order) {
        unsigned int total = 0;
        auto orderMenuItems = OrderMenuItemRepository::getInstance()->getByOrderId(order->id);
        for (auto orderMenuItem: *orderMenuItems) {
            auto menuItem = MenuItemRepository::getInstance()->getById(orderMenuItem->menuItemId);
            total += orderMenuItem->qty * menuItem->priceInCents;
        }
        return total;
    }

    vector<Order *> *OrderService::search(vector<Order *> *orders, string *searchBy) {
        auto result = new vector<Order *>();
        for (auto order: *orders) {
            auto orderMenuItems = OrderMenuItemRepository::getInstance()->getByOrderId(order->id);
            for (auto orderMenuItem: *orderMenuItems) {
                auto menuItem = MenuItemRepository::getInstance()->getById(orderMenuItem->menuItemId);
                if (string(menuItem->name).find(*searchBy) != string::npos) {
                    result->push_back(order);
                    break;
                }
            }
        }
        return result;
    }

    vector<Order *> *OrderService::filter(vector<Order *> *orders, FilterOption *filterOptions) {
        auto result = new vector<Order *>();
        if (filterOptions == nullptr) {
            return result;
        }
        for (auto order: *orders) {
            auto orderMenuItems = OrderMenuItemRepository::getInstance()
                    ->getByOrderId(order->id);
            for (auto orderMenuItem: *orderMenuItems) {
                if ((*filterOptions == FilterOption::NOT_SERVED) && !orderMenuItem->isServed) {
                    result->push_back(order);
                    break;
                }
            }
        }
        return result;
    }

    vector<Order *> *OrderService::sort(vector<Order *> *orders, SortOption *sortOptions) {
        auto result = new vector<Order *>();
        if (sortOptions == nullptr) {
            return result;
        }
        for (auto order: *orders)
            result->push_back(order);

        auto n = result->size();
        for (auto i = 0; i < n - 1; ++i) {
            for (auto j = 0; j < n - i - 1; ++j) {
                auto first = result->at(j);
                auto second = result->at(j + 1);

                if (*sortOptions == SortOption::TOTAL_PRICE_ASC) {
                    auto firstPrice = OrderService::getInstance()->getOrderTotalPrice(first);
                    auto secondPrice = OrderService::getInstance()->getOrderTotalPrice(second);
                    if (firstPrice > secondPrice) {
                        result->at(j) = second;
                        result->at(j + 1) = first;
                    }
                }

            }
        }
        return result;
    }

    bool OrderService::getIsFullyServed(Order *order) {

        auto orderMenuItems = OrderMenuItemRepository::getInstance()->getByOrderId(order->id);
        if (orderMenuItems->empty()) {
            return false;
        }
        for (auto orderMenuItem: *orderMenuItems) {
            if (!orderMenuItem->isServed) {
                return false;
            }
        }
        return true;
    }

    string OrderService::getDescription(Order *order) {
        auto orderMenuItems = OrderMenuItemRepository::getInstance()->getByOrderId(order->id);
        string description;
        for (auto i = 0; i < orderMenuItems->size(); i++) {
            auto orderMenuItem = orderMenuItems->at(i);
            auto menuItem = MenuItemRepository::getInstance()->getById(orderMenuItem->menuItemId);
            description += string(menuItem->name);

            if (i + 1 < orderMenuItems->size()) {
                description += ", ";
            }
        }
        return description;
    }
}
