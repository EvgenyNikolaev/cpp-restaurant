#ifndef RESTARAUNT_NAVIGATION_H
#define RESTARAUNT_NAVIGATION_H

#include <vector>
#include <string>

namespace service {
    struct Command;

    class Screen {
    public:
        virtual void display() = 0;

        virtual std::vector<Command *> *getCommands();

        virtual bool handleCommandInput(std::string input) = 0;

        virtual std::string getName() = 0;
    };

    struct Command {
        std::string *description;
        const std::string *command;

        explicit Command(const std::string *command, std::string *description);
    };

    class Navigator {
    private:
        constexpr static const std::string COMMAND_BACK = "back";
        constexpr static const std::string COMMAND_EXIT = "exit";

        std::vector<Screen *> *stack;

        void displayCommandPrompt(Screen *screen);

        static Navigator *instance;


    public:
        Navigator();

        static const int windowWidth = 120;

        static Navigator *getInstance();

        void navigate(Screen *screen, bool replace = false);

        void goBack();

        void putScreenOnStage(Screen *screen);
    };

}


#endif