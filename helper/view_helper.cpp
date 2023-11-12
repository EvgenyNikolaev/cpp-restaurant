
#include <string>
#include "view_helper.h"
#include "../service/navigation.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace service;

namespace helper {
    void ViewHelper::printHorizontalRule() {
        std::cout << std::endl << std::string(Navigator::windowWidth, '-') << std::endl;
    }

    std::string ViewHelper::formatPrice(unsigned int priceInCents) {
        auto main = floor((double) priceInCents / 100);
        auto fraction = priceInCents - (main * 100);
        auto output = std::to_string((int) main) + ".";
        if (fraction < 10) {
            output += "0";
        }
        output += std::to_string((int) fraction);
        return output;
    }

    void ViewHelper::printProperty(std::string property, std::string value) {
        std::cout << std::setw(20) << std::left << std::setfill('.') << property + ":"
                  << std::setw(30) << std::right << std::setfill('.') << value << std::endl;
    }
}

