#include "file_task_repository.h"
#include "repository_exceptions.h"
#include "error_logger.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>

using json = nlohmann::json;
namespace fs = std::filesystem;

FileTaskRepository::FileTaskRepository(const std::string& filePath)
    : filePath(filePath), maxId(0) {
}

std::vector<Task> FileTaskRepository::loadTasks() {
    std::vector<Task> tasks;

    // Check if file exists
    if (!fs::exists(filePath)) {
        try {
            // Create empty file
            std::ofstream file(filePath);
            if (!file.is_open()) {
                std::string errorMsg = "Cannot create file: " + filePath;
                ErrorLogger::logError("loadTasks", errorMsg);
                throw FileIOException(errorMsg);
            }
            file << "[]";
            file.close();
            return tasks;
        } catch (const std::filesystem::filesystem_error& e) {
            std::string errorMsg = "Filesystem error creating file '" + filePath + "': " + e.what();
            ErrorLogger::logError("loadTasks", errorMsg);
            throw FileIOException(errorMsg);
        }
    }

    // Read file
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::string errorMsg = "Cannot open file for reading: " + filePath;
        ErrorLogger::logError("loadTasks", errorMsg);
        throw FileIOException(errorMsg);
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
        } else {
            std::string errorMsg = "Invalid JSON format: expected array";
            ErrorLogger::logError("loadTasks", errorMsg);
            throw JsonParseException(errorMsg);
        }
    } catch (const nlohmann::json::exception& e) {
        std::string errorMsg = "Failed to parse JSON from '" + filePath + "': " + e.what();
        ErrorLogger::logError("loadTasks", errorMsg);
        tasks.clear();
        throw JsonParseException(errorMsg);
    } catch (const std::ios_base::failure& e) {
        std::string errorMsg = "File stream error reading '" + filePath + "': " + e.what();
        ErrorLogger::logError("loadTasks", errorMsg);
        throw FileIOException(errorMsg);
    }

    file.close();
    return tasks;
}

void FileTaskRepository::saveTasks(const std::vector<Task>& tasks) {
    json j = json::array();

    try {
        for (const auto& task : tasks) {
            j.push_back(task.toJson());
            
            // Update maxId while saving
            if (task.getId() > maxId) {
                maxId = task.getId();
            }
        }

        std::ofstream file(filePath);
        if (!file.is_open()) {
            std::string errorMsg = "Cannot open file for writing: " + filePath;
            ErrorLogger::logError("saveTasks", errorMsg);
            throw FileIOException(errorMsg);
        }
        
        file << j.dump(2); // Pretty print with 2-space indent
        
        if (file.fail()) {
            std::string errorMsg = "Failed to write to file: " + filePath;
            ErrorLogger::logError("saveTasks", errorMsg);
            throw FileIOException(errorMsg);
        }
        
        file.close();
    } catch (const nlohmann::json::exception& e) {
        std::string errorMsg = "Failed to serialize tasks to JSON: " + std::string(e.what());
        ErrorLogger::logError("saveTasks", errorMsg);
        throw JsonParseException(errorMsg);
    } catch (const std::filesystem::filesystem_error& e) {
        std::string errorMsg = "Filesystem error writing to '" + filePath + "': " + e.what();
        ErrorLogger::logError("saveTasks", errorMsg);
        throw FileIOException(errorMsg);
    }
}

int FileTaskRepository::getNextId() const {
    return maxId + 1;
}

void FileTaskRepository::resetIdCounter() {
    maxId = 0;
}
