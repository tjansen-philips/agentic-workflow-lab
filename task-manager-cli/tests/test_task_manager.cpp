#include <gtest/gtest.h>
#include "task_manager.h"
#include "task_repository.h"
#include <filesystem>

namespace fs = std::filesystem;

class TaskManagerTest : public ::testing::Test {
protected:
    std::string testFilePath;
    
    void SetUp() override {
        testFilePath = "test_manager_tasks.json";
        if (fs::exists(testFilePath)) {
            fs::remove(testFilePath);
        }
    }
    
    void TearDown() override {
        if (fs::exists(testFilePath)) {
            fs::remove(testFilePath);
        }
    }
};

// Test adding a task
TEST_F(TaskManagerTest, AddTask) {
    TaskRepository repo(testFilePath);
    TaskManager manager(repo);
    
    int taskId = manager.addTask("Buy groceries");
    
    EXPECT_EQ(taskId, 1);
    
    std::vector<Task> tasks = manager.listTasks();
    ASSERT_EQ(tasks.size(), 1);
    EXPECT_EQ(tasks[0].getId(), 1);
    EXPECT_EQ(tasks[0].getDescription(), "Buy groceries");
    EXPECT_FALSE(tasks[0].isCompleted());
}

// Test adding multiple tasks
TEST_F(TaskManagerTest, AddMultipleTasks) {
    TaskRepository repo(testFilePath);
    TaskManager manager(repo);
    
    int id1 = manager.addTask("Task 1");
    int id2 = manager.addTask("Task 2");
    int id3 = manager.addTask("Task 3");
    
    EXPECT_EQ(id1, 1);
    EXPECT_EQ(id2, 2);
    EXPECT_EQ(id3, 3);
    
    std::vector<Task> tasks = manager.listTasks();
    ASSERT_EQ(tasks.size(), 3);
}

// Test adding task with empty description (should be allowed but not ideal)
TEST_F(TaskManagerTest, AddTaskEmptyDescription) {
    TaskRepository repo(testFilePath);
    TaskManager manager(repo);
    
    int taskId = manager.addTask("");
    
    EXPECT_EQ(taskId, 1);
    
    std::vector<Task> tasks = manager.listTasks();
    ASSERT_EQ(tasks.size(), 1);
    EXPECT_EQ(tasks[0].getDescription(), "");
}

// Test listing tasks when empty
TEST_F(TaskManagerTest, ListTasksEmpty) {
    TaskRepository repo(testFilePath);
    TaskManager manager(repo);
    
    std::vector<Task> tasks = manager.listTasks();
    EXPECT_TRUE(tasks.empty());
}

// Test completing a task
TEST_F(TaskManagerTest, CompleteTask) {
    TaskRepository repo(testFilePath);
    TaskManager manager(repo);
    
    manager.addTask("Task to complete");
    
    bool success = manager.completeTask(1);
    EXPECT_TRUE(success);
    
    std::vector<Task> tasks = manager.listTasks();
    ASSERT_EQ(tasks.size(), 1);
    EXPECT_TRUE(tasks[0].isCompleted());
}

// Test completing non-existent task
TEST_F(TaskManagerTest, CompleteNonExistentTask) {
    TaskRepository repo(testFilePath);
    TaskManager manager(repo);
    
    bool success = manager.completeTask(999);
    EXPECT_FALSE(success);
}

// Test completing task with mixed tasks
TEST_F(TaskManagerTest, CompleteSpecificTask) {
    TaskRepository repo(testFilePath);
    TaskManager manager(repo);
    
    manager.addTask("Task 1");
    manager.addTask("Task 2");
    manager.addTask("Task 3");
    
    manager.completeTask(2);
    
    std::vector<Task> tasks = manager.listTasks();
    ASSERT_EQ(tasks.size(), 3);
    EXPECT_FALSE(tasks[0].isCompleted()); // Task 1
    EXPECT_TRUE(tasks[1].isCompleted());  // Task 2
    EXPECT_FALSE(tasks[2].isCompleted()); // Task 3
}

// Test persistence - tasks should survive manager restart
TEST_F(TaskManagerTest, PersistenceAcrossRestarts) {
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        manager.addTask("Persistent task");
        manager.completeTask(1);
    }
    
    // Create new manager instance with same file
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        std::vector<Task> tasks = manager.listTasks();
        ASSERT_EQ(tasks.size(), 1);
        EXPECT_EQ(tasks[0].getDescription(), "Persistent task");
        EXPECT_TRUE(tasks[0].isCompleted());
    }
}

// Test ID continuity after restart
TEST_F(TaskManagerTest, IdContinuityAfterRestart) {
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        manager.addTask("Task 1");
        manager.addTask("Task 2");
    }
    
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        int id = manager.addTask("Task 3");
        EXPECT_EQ(id, 3); // Should continue from previous max ID
    }
}

// Test clearing all tasks
TEST_F(TaskManagerTest, ClearAllTasks) {
    TaskRepository repo(testFilePath);
    TaskManager manager(repo);
    
    manager.addTask("Task 1");
    manager.addTask("Task 2");
    manager.addTask("Task 3");
    
    EXPECT_EQ(manager.listTasks().size(), 3);
    
    manager.clearAllTasks();
    
    EXPECT_TRUE(manager.listTasks().empty());
}

// Test clearing empty list
TEST_F(TaskManagerTest, ClearEmptyList) {
    TaskRepository repo(testFilePath);
    TaskManager manager(repo);
    
    EXPECT_TRUE(manager.listTasks().empty());
    
    manager.clearAllTasks(); // Should not throw or error
    
    EXPECT_TRUE(manager.listTasks().empty());
}

// Test ID reset after clear
TEST_F(TaskManagerTest, IdResetAfterClear) {
    TaskRepository repo(testFilePath);
    TaskManager manager(repo);
    
    manager.addTask("Task 1");
    manager.addTask("Task 2");
    int lastId = manager.addTask("Task 3");
    EXPECT_EQ(lastId, 3);
    
    manager.clearAllTasks();
    
    int newId = manager.addTask("New task");
    EXPECT_EQ(newId, 1); // Should reset to 1
}

// Test clear persistence
TEST_F(TaskManagerTest, ClearPersistence) {
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        manager.addTask("Task 1");
        manager.addTask("Task 2");
        manager.clearAllTasks();
    }
    
    // Verify clear was persisted
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        EXPECT_TRUE(manager.listTasks().empty());
        
        int newId = manager.addTask("New task");
        EXPECT_EQ(newId, 1); // ID should be reset
    }
}
