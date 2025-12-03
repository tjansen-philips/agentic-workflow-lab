#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <vector>
#include <string>
#include "task.h"
#include "i_task_repository.h"

class TaskManager {
private:
    ITaskRepository& repository;
    std::vector<Task> tasks;

public:
    // Constructor
    explicit TaskManager(ITaskRepository& repository);

    // Add a new task
    int addTask(const std::string& description);

    // List all tasks
    std::vector<Task> listTasks() const;

    // Complete a task by ID
    bool completeTask(int id);

    // Clear all tasks
    void clearAllTasks();
};

#endif // TASK_MANAGER_H
