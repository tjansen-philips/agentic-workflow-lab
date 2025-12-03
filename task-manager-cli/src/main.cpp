#include "cli.h"
#include "task_manager.h"
#include "file_task_repository.h"
#include "repository_exceptions.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    try {
        // Determine executable directory for tasks.json
        fs::path exePath = fs::current_path();
        std::string tasksFile = (exePath / "tasks.json").string();

        // Initialize repository and manager
        FileTaskRepository repository(tasksFile);
        TaskManager manager(repository);

        // Parse command
        CLI cli;
        Command cmd = cli.parseCommand(argc, argv);

        // Execute command
        switch (cmd.type) {
            case CommandType::ADD: {
                int id = manager.addTask(cmd.argument);
                cli.displaySuccess("Task added with ID: " + std::to_string(id));
                break;
            }

            case CommandType::LIST: {
                std::vector<Task> tasks = manager.listTasks();
                cli.displayTasks(tasks);
                break;
            }

            case CommandType::COMPLETE: {
                int id = std::stoi(cmd.argument);
                bool success = manager.completeTask(id);
                
                if (success) {
                    cli.displaySuccess("Task " + std::to_string(id) + " marked as completed");
                } else {
                    cli.displayError("Task not found: " + std::to_string(id));
                    cli.displayHelp();
                    return 1;
                }
                break;
            }

            case CommandType::CLEAR: {
                manager.clearAllTasks();
                cli.displaySuccess("All tasks cleared");
                break;
            }

            case CommandType::HELP: {
                cli.displayHelp();
                break;
            }

            case CommandType::INVALID:
            default: {
                cli.displayError("Invalid command");
                cli.displayHelp();
                return 1;
            }
        }

        return 0;
    }
    catch (const JsonParseException& e) {
        std::cerr << "JSON Error: " << e.what() << "\n";
        std::cerr << "The tasks file may be corrupted. Please check or delete the tasks.json file.\n";
        return 1;
    }
    catch (const FileIOException& e) {
        std::cerr << "File Error: " << e.what() << "\n";
        std::cerr << "Please check file permissions and available disk space.\n";
        return 1;
    }
    catch (const RepositoryException& e) {
        std::cerr << "Repository Error: " << e.what() << "\n";
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        CLI cli;
        cli.displayHelp();
        return 1;
    }
}
