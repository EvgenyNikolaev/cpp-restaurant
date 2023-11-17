#ifndef RESTARAUNT_NAVIGATION_H
#define RESTARAUNT_NAVIGATION_H

#include <vector>
#include <string>

using namespace std;

namespace service {
    struct Command;

    class Screen {
    public:
        virtual void display() = 0;

        virtual vector<Command *> *getCommands();

        virtual bool handleCommandInput(string input) = 0;

        virtual string getName() = 0;
    };

    struct Command {
        string *description;
        const string *command;

        explicit Command(const string *command, string *description);
    };

    class Navigator {
    private:
        constexpr static const string COMMAND_BACK = "back";
        constexpr static const string COMMAND_EXIT = "exit";

        vector<Screen *> *stack;

        void displayCommandPrompt(Screen *screen, bool printCommands = true);

        static Navigator *instance;

        void printAvailableCommands(Screen *screen);

        void putScreenOnStage(Screen *screen);

    public:
        Navigator();

        static const int windowWidth = 120;

        static Navigator *getInstance();

        void navigate(Screen *screen, bool replace = false);

        void goBack();
    };

}


#endif