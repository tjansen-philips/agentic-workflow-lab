#ifndef MOCK_TASK_REPOSITORY_H
#define MOCK_TASK_REPOSITORY_H

#include <vector>
#include "task.h"
#include "i_task_repository.h"

/**
 * Mock implementation of ITaskRepository for unit testing.
 * Stores tasks in memory without file I/O.
 */
class MockTaskRepository : public ITaskRepository {
private:
    std::vector<Task> tasks;
    int maxId;

public:
    // Constructor
    MockTaskRepository() : maxId(0) {}

    // Load tasks from memory
    std::vector<Task> loadTasks() override {
        // Update maxId based on loaded tasks
        maxId = 0;
        for (const auto& task : tasks) {
            if (task.getId() > maxId) {
                maxId = task.getId();
            }
        }
        return tasks;
    }

    // Save tasks to memory
    void saveTasks(const std::vector<Task>& newTasks) override {
        tasks = newTasks;
        // Update maxId while saving
        maxId = 0;
        for (const auto& task : tasks) {
            if (task.getId() > maxId) {
                maxId = task.getId();
            }
        }
    }

    // Get next available ID
    int getNextId() const override {
        return maxId + 1;
    }

    // Reset ID counter to 0 (next ID will be 1)
    void resetIdCounter() override {
        maxId = 0;
    }

    // Test helper: Clear all tasks
    void clear() {
        tasks.clear();
        maxId = 0;
    }
};

#endif // MOCK_TASK_REPOSITORY_H
