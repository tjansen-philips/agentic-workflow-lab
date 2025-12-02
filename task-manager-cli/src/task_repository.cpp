#include "task_repository.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>

using json = nlohmann::json;
namespace fs = std::filesystem;

TaskRepository::TaskRepository(const std::string& filePath)
    : filePath(filePath), maxId(0) {
}

std::vector<Task> TaskRepository::loadTasks() {
    std::vector<Task> tasks;

    // Check if file exists
    if (!fs::exists(filePath)) {
        // Create empty file
        std::ofstream file(filePath);
        file << "[]";
        file.close();
        return tasks;
    }

    // Read file
    std::ifstream file(filePath);
    if (!file.is_open()) {
        // If we can't open, return empty vector
        return tasks;
    }

    json j;
    try {
        file >> j;
        
        // Parse tasks from JSON array
        if (j.is_array()) {
            for (const auto& taskJson : j) {
                Task task = Task::fromJson(taskJson);
                tasks.push_back(task);
                
                // Track max ID
                if (task.getId() > maxId) {
                    maxId = task.getId();
                }
            }
        }
    } catch (...) {
        // If JSON parsing fails, return empty vector
        tasks.clear();
    }

    file.close();
    return tasks;
}

void TaskRepository::saveTasks(const std::vector<Task>& tasks) {
    json j = json::array();

    for (const auto& task : tasks) {
        j.push_back(task.toJson());
        
        // Update maxId while saving
        if (task.getId() > maxId) {
            maxId = task.getId();
        }
    }

    std::ofstream file(filePath);
    file << j.dump(2); // Pretty print with 2-space indent
    file.close();
}

int TaskRepository::getNextId() const {
    return maxId + 1;
}
