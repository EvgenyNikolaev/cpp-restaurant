#include "service/navigation.h"
#include "screen/main_screen.h"

int main() {
    Navigator::getInstance()->navigate(new screen::MainScreen());
    return 0;
}
