#ifndef RESTARAUNT_VIEW_HELPER_H
#define RESTARAUNT_VIEW_HELPER_H

using namespace std;

namespace helper {
    class ViewHelper {
    public:
        static void printHorizontalRule();

        static string formatPrice(unsigned int priceInCents);

        static void printProperty(string property, string value);

        static void integerInput(string property, unsigned int *value);
    };
}


#endif
