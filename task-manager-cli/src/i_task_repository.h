#ifndef I_TASK_REPOSITORY_H
#define I_TASK_REPOSITORY_H

#include <string>
#include <vector>
#include "task.h"

/**
 * Abstract interface for task repository operations.
 * This allows for dependency inversion and better testability.
 */
class ITaskRepository {
public:
    virtual ~ITaskRepository() = default;

    // Load tasks from storage
    virtual std::vector<Task> loadTasks() = 0;

    // Save tasks to storage
    virtual void saveTasks(const std::vector<Task>& tasks) = 0;

    // Get next available ID
    virtual int getNextId() const = 0;

    // Reset ID counter to 0 (next ID will be 1)
    virtual void resetIdCounter() = 0;
};

#endif // I_TASK_REPOSITORY_H
