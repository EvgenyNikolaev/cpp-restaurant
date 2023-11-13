
#include <string>
#include "view_helper.h"
#include "../service/navigation.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
using namespace service;

namespace helper {
    void ViewHelper::printHorizontalRule() {
        cout << endl << string(Navigator::windowWidth, '-') << endl;
    }

    string ViewHelper::formatPrice(unsigned int priceInCents) {
        auto main = floor((double) priceInCents / 100);
        auto fraction = priceInCents - (main * 100);
        auto output = to_string((int) main) + ".";
        if (fraction < 10) {
            output += "0";
        }
        output += to_string((int) fraction);
        return output;
    }

    void ViewHelper::printProperty(string property, string value) {
        cout << setw(20) << left << setfill('.') << property + ":"
                  << setw(30) << right << setfill('.') << value << endl;
    }
}

