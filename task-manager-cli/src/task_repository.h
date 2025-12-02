#ifndef TASK_REPOSITORY_H
#define TASK_REPOSITORY_H

#include <string>
#include <vector>
#include "task.h"

class TaskRepository {
private:
    std::string filePath;
    int maxId;

public:
    // Constructor
    explicit TaskRepository(const std::string& filePath);

    // Load tasks from file
    std::vector<Task> loadTasks();

    // Save tasks to file
    void saveTasks(const std::vector<Task>& tasks);

    // Get next available ID
    int getNextId() const;

    // Reset ID counter to 0 (next ID will be 1)
    void resetIdCounter();
};

#endif // TASK_REPOSITORY_H
