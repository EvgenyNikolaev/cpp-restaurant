
#include <string>
#include "view_helper.h"
#include "../service/navigation.h"
#include <iostream>

using namespace service;

namespace helper {
    void ViewHelper::printHorizontalRule() {
        std::cout << std::endl << std::string(Navigator::windowWidth, '-') << std::endl;
    }
}

