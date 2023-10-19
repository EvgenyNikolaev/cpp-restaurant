cmake_minimum_required(VERSION 3.26)
project(restaraunt)

set(CMAKE_CXX_STANDARD 20)

add_executable(restaraunt main.cpp
        service/navigation.h
        service/navigation.cpp
        screen/orders_list_screen.cpp
        screen/orders_list_screen.h
        screen/main_screen.cpp
        screen/main_screen.h
        repository/order_repository.cpp
        repository/order_repository.h
        model/menu_item.h
        model/order_menu_item.h
        model/order.h
        screen/order_screen.cpp
        screen/order_screen.h
        screen/menu_items_screen.cpp
        repository/menu_item_repository.cpp
        helper/view_helper.h
        helper/view_helper.cpp
)
