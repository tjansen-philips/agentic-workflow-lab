#ifndef FILE_TASK_REPOSITORY_H
#define FILE_TASK_REPOSITORY_H

#include <string>
#include <vector>
#include "task.h"
#include "i_task_repository.h"

class FileTaskRepository : public ITaskRepository {
private:
    std::string filePath;
    int maxId;

public:
    // Constructor
    explicit FileTaskRepository(const std::string& filePath);

    // Load tasks from file
    std::vector<Task> loadTasks() override;

    // Save tasks to file
    void saveTasks(const std::vector<Task>& tasks) override;

    // Get next available ID
    int getNextId() const override;

    // Reset ID counter to 0 (next ID will be 1)
    void resetIdCounter() override;
};

#endif // FILE_TASK_REPOSITORY_H
