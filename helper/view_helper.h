#ifndef RESTARAUNT_VIEW_HELPER_H
#define RESTARAUNT_VIEW_HELPER_H

namespace helper {
    class ViewHelper {
    public:
        static void printHorizontalRule();
        static std::string formatPrice(unsigned int priceInCents);
        static void printProperty(std::string property, std::string value);
    };
}


#endif
