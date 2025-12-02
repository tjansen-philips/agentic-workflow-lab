#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <vector>
#include <string>
#include "task.h"
#include "task_repository.h"

class TaskManager {
private:
    TaskRepository& repository;
    std::vector<Task> tasks;

public:
    // Constructor
    explicit TaskManager(TaskRepository& repository);

    // Add a new task
    int addTask(const std::string& description);

    // List all tasks
    std::vector<Task> listTasks() const;

    // Complete a task by ID
    bool completeTask(int id);
};

#endif // TASK_MANAGER_H
