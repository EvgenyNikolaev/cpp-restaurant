#ifndef RESTARAUNT_NAVIGATION_H
#define RESTARAUNT_NAVIGATION_H

#include <vector>
#include <string>

namespace service {
    struct Command;

    struct Screen {
        virtual void display() = 0;

        virtual std::vector<Command *> *getCommands();

        virtual bool handleCommandInput(std::string input) = 0;

        virtual std::string getName() = 0;
    };

    struct Command {
        std::string *description;

        explicit Command(std::string *description);
    };


    class Navigator {
    private:
        std::vector<Screen *> *stack;

        void displayCommandPrompt(Screen *screen);

        static Navigator *instance;


    public:
        Navigator();

        static Navigator *getInstance();

        void navigate(Screen *screen, bool replace = false);

        void goBack();
    };

}


#endif