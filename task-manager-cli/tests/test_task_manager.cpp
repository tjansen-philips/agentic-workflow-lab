#include <gtest/gtest.h>
#include "task_manager.h"
#include "mock_task_repository.h"
#include "file_task_repository.h"
#include <filesystem>

namespace fs = std::filesystem;

class TaskManagerTest : public ::testing::Test {
};

// Separate test fixture for persistence tests that need file I/O
class TaskManagerPersistenceTest : public ::testing::Test {
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
    MockTaskRepository repo;
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
    MockTaskRepository repo;
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
    MockTaskRepository repo;
    TaskManager manager(repo);
    
    int taskId = manager.addTask("");
    
    EXPECT_EQ(taskId, 1);
    
    std::vector<Task> tasks = manager.listTasks();
    ASSERT_EQ(tasks.size(), 1);
    EXPECT_EQ(tasks[0].getDescription(), "");
}

// Test listing tasks when empty
TEST_F(TaskManagerTest, ListTasksEmpty) {
    MockTaskRepository repo;
    TaskManager manager(repo);
    
    std::vector<Task> tasks = manager.listTasks();
    EXPECT_TRUE(tasks.empty());
}

// Test completing a task
TEST_F(TaskManagerTest, CompleteTask) {
    MockTaskRepository repo;
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
    MockTaskRepository repo;
    TaskManager manager(repo);
    
    bool success = manager.completeTask(999);
    EXPECT_FALSE(success);
}

// Test completing task with mixed tasks
TEST_F(TaskManagerTest, CompleteSpecificTask) {
    MockTaskRepository repo;
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
TEST_F(TaskManagerPersistenceTest, PersistenceAcrossRestarts) {
    {
        FileTaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        manager.addTask("Persistent task");
        manager.completeTask(1);
    }
    
    // Create new manager instance with same file
    {
        FileTaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        std::vector<Task> tasks = manager.listTasks();
        ASSERT_EQ(tasks.size(), 1);
        EXPECT_EQ(tasks[0].getDescription(), "Persistent task");
        EXPECT_TRUE(tasks[0].isCompleted());
    }
}

// Test ID continuity after restart
TEST_F(TaskManagerPersistenceTest, IdContinuityAfterRestart) {
    {
        FileTaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        manager.addTask("Task 1");
        manager.addTask("Task 2");
    }
    
    {
        FileTaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        int id = manager.addTask("Task 3");
        EXPECT_EQ(id, 3); // Should continue from previous max ID
    }
}

// Test clearing all tasks
TEST_F(TaskManagerTest, ClearAllTasks) {
    MockTaskRepository repo;
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
    MockTaskRepository repo;
    TaskManager manager(repo);
    
    EXPECT_TRUE(manager.listTasks().empty());
    
    manager.clearAllTasks(); // Should not throw or error
    
    EXPECT_TRUE(manager.listTasks().empty());
}

// Test ID reset after clear
TEST_F(TaskManagerTest, IdResetAfterClear) {
    MockTaskRepository repo;
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
TEST_F(TaskManagerPersistenceTest, ClearPersistence) {
    {
        FileTaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        manager.addTask("Task 1");
        manager.addTask("Task 2");
        manager.clearAllTasks();
    }
    
    // Verify clear was persisted
    {
        FileTaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        EXPECT_TRUE(manager.listTasks().empty());
        
        int newId = manager.addTask("New task");
        EXPECT_EQ(newId, 1); // ID should be reset
    }
}

// Test task ordering is preserved
TEST_F(TaskManagerTest, TaskOrderingPreserved) {
    MockTaskRepository repo;
    TaskManager manager(repo);
    
    manager.addTask("First task");
    manager.addTask("Second task");
    manager.addTask("Third task");
    
    std::vector<Task> tasks = manager.listTasks();
    ASSERT_EQ(tasks.size(), 3);
    EXPECT_EQ(tasks[0].getDescription(), "First task");
    EXPECT_EQ(tasks[1].getDescription(), "Second task");
    EXPECT_EQ(tasks[2].getDescription(), "Third task");
}

// Test completing multiple tasks
TEST_F(TaskManagerTest, CompleteMultipleTasks) {
    MockTaskRepository repo;
    TaskManager manager(repo);
    
    manager.addTask("Task 1");
    manager.addTask("Task 2");
    manager.addTask("Task 3");
    manager.addTask("Task 4");
    
    manager.completeTask(2);
    manager.completeTask(4);
    
    std::vector<Task> tasks = manager.listTasks();
    ASSERT_EQ(tasks.size(), 4);
    EXPECT_FALSE(tasks[0].isCompleted());
    EXPECT_TRUE(tasks[1].isCompleted());
    EXPECT_FALSE(tasks[2].isCompleted());
    EXPECT_TRUE(tasks[3].isCompleted());
}

// Test that repository is called with correct data
TEST_F(TaskManagerTest, RepositorySavesCorrectly) {
    MockTaskRepository repo;
    TaskManager manager(repo);
    
    manager.addTask("Test task");
    
    // Verify the repository has the task saved
    const std::vector<Task>& savedTasks = repo.getTasks();
    ASSERT_EQ(savedTasks.size(), 1);
    EXPECT_EQ(savedTasks[0].getId(), 1);
    EXPECT_EQ(savedTasks[0].getDescription(), "Test task");
    EXPECT_FALSE(savedTasks[0].isCompleted());
}
