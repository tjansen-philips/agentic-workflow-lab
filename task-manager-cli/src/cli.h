#ifndef CLI_H
#define CLI_H

#include <string>
#include <vector>
#include <iostream>
#include "task.h"

enum class CommandType {
    ADD,
    LIST,
    COMPLETE,
    CLEAR,
    HELP,
    INVALID
};

struct Command {
    CommandType type;
    std::string argument;
};

class CLI {
public:
    CLI() = default;

    // Parse command-line arguments
    Command parseCommand(int argc, char* argv[]);

    // Display functions
    void displayHelp(std::ostream& out = std::cout);
    void displayTasks(const std::vector<Task>& tasks, std::ostream& out = std::cout);
    void displaySuccess(const std::string& message, std::ostream& out = std::cout);
    void displayError(const std::string& message, std::ostream& out = std::cout);
};

#endif // CLI_H
