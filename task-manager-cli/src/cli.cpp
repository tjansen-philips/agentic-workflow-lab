#include "cli.h"
#include <sstream>

Command CLI::parseCommand(int argc, char* argv[]) {
    Command cmd;
    cmd.type = CommandType::INVALID;
    cmd.argument = "";

    if (argc < 2) {
        return cmd;
    }

    std::string command = argv[1];

    if (command == "add") {
        if (argc < 3) {
            return cmd;
        }
        
        // Join all arguments after "add" into a single description
        std::stringstream ss;
        for (int i = 2; i < argc; i++) {
            if (i > 2) ss << " ";
            ss << argv[i];
        }
        
        cmd.type = CommandType::ADD;
        cmd.argument = ss.str();
    }
    else if (command == "list") {
        cmd.type = CommandType::LIST;
    }
    else if (command == "complete") {
        if (argc < 3) {
            return cmd;
        }
        
        cmd.type = CommandType::COMPLETE;
        cmd.argument = argv[2];
    }
    else if (command == "--help" || command == "-h") {
        cmd.type = CommandType::HELP;
    }
    else {
        cmd.type = CommandType::INVALID;
    }

    return cmd;
}

void CLI::displayHelp(std::ostream& out) {
    out << "Task Manager CLI - Simple task management\n\n";
    out << "Usage:\n";
    out << "  task-manager add <description>    Add a new task\n";
    out << "  task-manager list                  List all tasks\n";
    out << "  task-manager complete <id>         Mark a task as completed\n";
    out << "  task-manager --help                Show this help message\n\n";
    out << "Examples:\n";
    out << "  task-manager add Buy groceries\n";
    out << "  task-manager list\n";
    out << "  task-manager complete 1\n";
}

void CLI::displayTasks(const std::vector<Task>& tasks, std::ostream& out) {
    if (tasks.empty()) {
        out << "No tasks found.\n";
        return;
    }

    for (const auto& task : tasks) {
        std::string status = task.isCompleted() ? "[X]" : "[ ]";
        out << "[" << task.getId() << "] " << status << " " 
            << task.getDescription() << "\n";
    }
}

void CLI::displaySuccess(const std::string& message, std::ostream& out) {
    out << message << "\n";
}

void CLI::displayError(const std::string& message, std::ostream& out) {
    out << "Error: " << message << "\n";
}
