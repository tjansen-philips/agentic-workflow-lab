#include "task_manager.h"

TaskManager::TaskManager(TaskRepository& repository)
    : repository(repository) {
    // Load existing tasks from repository
    tasks = repository.loadTasks();
}

int TaskManager::addTask(const std::string& description) {
    // Get next available ID
    int id = repository.getNextId();
    
    // Create new task
    Task newTask(id, description, false);
    tasks.push_back(newTask);
    
    // Persist to repository
    repository.saveTasks(tasks);
    
    return id;
}

std::vector<Task> TaskManager::listTasks() const {
    return tasks;
}

bool TaskManager::completeTask(int id) {
    // Find task by ID
    for (auto& task : tasks) {
        if (task.getId() == id) {
            task.setCompleted(true);
            
            // Persist changes
            repository.saveTasks(tasks);
            
            return true;
        }
    }
    
    // Task not found
    return false;
}

void TaskManager::clearAllTasks() {
    // Clear in-memory task list
    tasks.clear();
    
    // Reset ID counter
    repository.resetIdCounter();
    
    // Persist empty list
    repository.saveTasks(tasks);
}
