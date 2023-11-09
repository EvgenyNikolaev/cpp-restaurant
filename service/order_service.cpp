#include "order_service.h"
#include "../repository/order_menu_item_repository.h"
#include "../repository/menu_item_repository.h"

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
}
