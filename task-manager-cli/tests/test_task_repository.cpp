#include <gtest/gtest.h>
#include "file_task_repository.h"
#include "task.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class TaskRepositoryTest : public ::testing::Test {
protected:
    std::string testFilePath;
    
    void SetUp() override {
        // Use a temporary test file in the current directory
        testFilePath = "test_tasks.json";
        // Clean up any existing test file
        if (fs::exists(testFilePath)) {
            fs::remove(testFilePath);
        }
    }
    
    void TearDown() override {
        // Clean up test file after each test
        if (fs::exists(testFilePath)) {
            fs::remove(testFilePath);
        }
    }
};

// Test loading from non-existent file (should create empty file)
TEST_F(TaskRepositoryTest, LoadFromNonExistentFile) {
    FileTaskRepository repo(testFilePath);
    std::vector<Task> tasks = repo.loadTasks();
    
    EXPECT_TRUE(tasks.empty());
    EXPECT_TRUE(fs::exists(testFilePath));
}

// Test saving and loading tasks
TEST_F(TaskRepositoryTest, SaveAndLoadTasks) {
    FileTaskRepository repo(testFilePath);
    
    std::vector<Task> tasksToSave = {
        Task(1, "Task 1", false),
        Task(2, "Task 2", true),
        Task(3, "Task 3", false)
    };
    
    repo.saveTasks(tasksToSave);
    
    std::vector<Task> loadedTasks = repo.loadTasks();
    
    ASSERT_EQ(loadedTasks.size(), 3);
    EXPECT_EQ(loadedTasks[0].getId(), 1);
    EXPECT_EQ(loadedTasks[0].getDescription(), "Task 1");
    EXPECT_FALSE(loadedTasks[0].isCompleted());
    
    EXPECT_EQ(loadedTasks[1].getId(), 2);
    EXPECT_EQ(loadedTasks[1].getDescription(), "Task 2");
    EXPECT_TRUE(loadedTasks[1].isCompleted());
    
    EXPECT_EQ(loadedTasks[2].getId(), 3);
    EXPECT_EQ(loadedTasks[2].getDescription(), "Task 3");
    EXPECT_FALSE(loadedTasks[2].isCompleted());
}

// Test loading from existing file with tasks
TEST_F(TaskRepositoryTest, LoadFromExistingFile) {
    // Manually create a JSON file
    std::ofstream file(testFilePath);
    file << R"([
        {"id": 10, "description": "Existing task", "completed": false},
        {"id": 20, "description": "Another task", "completed": true}
    ])";
    file.close();
    
    FileTaskRepository repo(testFilePath);
    std::vector<Task> tasks = repo.loadTasks();
    
    ASSERT_EQ(tasks.size(), 2);
    EXPECT_EQ(tasks[0].getId(), 10);
    EXPECT_EQ(tasks[0].getDescription(), "Existing task");
    EXPECT_FALSE(tasks[0].isCompleted());
    
    EXPECT_EQ(tasks[1].getId(), 20);
    EXPECT_EQ(tasks[1].getDescription(), "Another task");
    EXPECT_TRUE(tasks[1].isCompleted());
}

// Test getNextId with empty repository
TEST_F(TaskRepositoryTest, GetNextIdEmpty) {
    FileTaskRepository repo(testFilePath);
    repo.loadTasks(); // Initialize with empty file
    
    EXPECT_EQ(repo.getNextId(), 1);
}

// Test getNextId with existing tasks
TEST_F(TaskRepositoryTest, GetNextIdWithExistingTasks) {
    FileTaskRepository repo(testFilePath);
    
    std::vector<Task> tasks = {
        Task(1, "Task 1", false),
        Task(5, "Task 5", false),
        Task(3, "Task 3", false)
    };
    
    repo.saveTasks(tasks);
    repo.loadTasks(); // Reload to update internal state
    
    EXPECT_EQ(repo.getNextId(), 6); // Should be max ID + 1
}

// Test saving empty task list
TEST_F(TaskRepositoryTest, SaveEmptyList) {
    FileTaskRepository repo(testFilePath);
    
    std::vector<Task> emptyTasks;
    repo.saveTasks(emptyTasks);
    
    std::vector<Task> loadedTasks = repo.loadTasks();
    EXPECT_TRUE(loadedTasks.empty());
}

// Test persistence across multiple operations
TEST_F(TaskRepositoryTest, MultipleSaveLoadCycles) {
    FileTaskRepository repo(testFilePath);
    
    // First save
    std::vector<Task> tasks1 = {Task(1, "First", false)};
    repo.saveTasks(tasks1);
    
    // Second save (overwrites)
    std::vector<Task> tasks2 = {
        Task(1, "First", true),
        Task(2, "Second", false)
    };
    repo.saveTasks(tasks2);
    
    std::vector<Task> loaded = repo.loadTasks();
    
    ASSERT_EQ(loaded.size(), 2);
    EXPECT_TRUE(loaded[0].isCompleted()); // Should reflect the update
    EXPECT_EQ(loaded[1].getId(), 2);
}

// Test resetting ID counter
TEST_F(TaskRepositoryTest, ResetIdCounter) {
    FileTaskRepository repo(testFilePath);
    
    // Add some tasks with high IDs
    std::vector<Task> tasks = {
        Task(5, "Task 5", false),
        Task(10, "Task 10", false)
    };
    repo.saveTasks(tasks);
    repo.loadTasks();
    
    EXPECT_EQ(repo.getNextId(), 11); // Before reset
    
    // Reset the counter
    repo.resetIdCounter();
    
    EXPECT_EQ(repo.getNextId(), 1); // After reset, should be 1
}

// Test reset on empty repository
TEST_F(TaskRepositoryTest, ResetIdCounterOnEmpty) {
    FileTaskRepository repo(testFilePath);
    repo.loadTasks(); // Empty list
    
    repo.resetIdCounter();
    
    EXPECT_EQ(repo.getNextId(), 1);
}
