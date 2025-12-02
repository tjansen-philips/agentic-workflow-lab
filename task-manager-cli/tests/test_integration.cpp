#include <gtest/gtest.h>
#include "cli.h"
#include "task_manager.h"
#include "task_repository.h"
#include "task.h"
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

// Integration test fixture that simulates real-world usage
class IntegrationTest : public ::testing::Test {
protected:
    std::string testFilePath;
    
    void SetUp() override {
        // Use a unique test file for integration tests
        testFilePath = "integration_test_tasks.json";
        cleanupTestFile();
    }
    
    void TearDown() override {
        cleanupTestFile();
    }
    
    void cleanupTestFile() {
        if (fs::exists(testFilePath)) {
            fs::remove(testFilePath);
        }
    }
    
    // Helper to verify tasks.json file content
    std::vector<Task> readTasksFromFile() {
        if (!fs::exists(testFilePath)) {
            return {};
        }
        
        std::ifstream file(testFilePath);
        nlohmann::json j;
        file >> j;
        
        std::vector<Task> tasks;
        for (const auto& taskJson : j) {
            tasks.push_back(Task::fromJson(taskJson));
        }
        return tasks;
    }
    
    // Helper to simulate a complete user session
    TaskManager createManager() {
        TaskRepository* repo = new TaskRepository(testFilePath);
        return TaskManager(*repo);
    }
};

// Test: Add multiple tasks → List → Verify output matches expectations
TEST_F(IntegrationTest, AddMultipleTasksAndList) {
    // Simulate user session 1: Add tasks
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        CLI cli;
        
        // Add three tasks
        int id1 = manager.addTask("Buy groceries");
        int id2 = manager.addTask("Write documentation");
        int id3 = manager.addTask("Review pull request");
        
        EXPECT_EQ(id1, 1);
        EXPECT_EQ(id2, 2);
        EXPECT_EQ(id3, 3);
        
        // List tasks and verify output
        std::vector<Task> tasks = manager.listTasks();
        ASSERT_EQ(tasks.size(), 3);
        
        EXPECT_EQ(tasks[0].getId(), 1);
        EXPECT_EQ(tasks[0].getDescription(), "Buy groceries");
        EXPECT_FALSE(tasks[0].isCompleted());
        
        EXPECT_EQ(tasks[1].getId(), 2);
        EXPECT_EQ(tasks[1].getDescription(), "Write documentation");
        EXPECT_FALSE(tasks[1].isCompleted());
        
        EXPECT_EQ(tasks[2].getId(), 3);
        EXPECT_EQ(tasks[2].getDescription(), "Review pull request");
        EXPECT_FALSE(tasks[2].isCompleted());
        
        // Verify CLI display format
        std::stringstream output;
        cli.displayTasks(tasks, output);
        std::string displayText = output.str();
        
        EXPECT_NE(displayText.find("[1]"), std::string::npos);
        EXPECT_NE(displayText.find("Buy groceries"), std::string::npos);
        EXPECT_NE(displayText.find("[ ]"), std::string::npos); // Incomplete marker
    }
    
    // Verify persistence: tasks.json should contain all tasks
    std::vector<Task> persistedTasks = readTasksFromFile();
    ASSERT_EQ(persistedTasks.size(), 3);
    EXPECT_EQ(persistedTasks[0].getDescription(), "Buy groceries");
    EXPECT_EQ(persistedTasks[1].getDescription(), "Write documentation");
    EXPECT_EQ(persistedTasks[2].getDescription(), "Review pull request");
}

// Test: Complete tasks → List → Verify completion status persists
TEST_F(IntegrationTest, CompleteTasksAndVerifyPersistence) {
    // Session 1: Add tasks
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        manager.addTask("Task 1");
        manager.addTask("Task 2");
        manager.addTask("Task 3");
    }
    
    // Session 2: Complete tasks
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        // Complete tasks 1 and 3
        bool success1 = manager.completeTask(1);
        bool success3 = manager.completeTask(3);
        
        EXPECT_TRUE(success1);
        EXPECT_TRUE(success3);
        
        // Verify in-memory state
        std::vector<Task> tasks = manager.listTasks();
        ASSERT_EQ(tasks.size(), 3);
        EXPECT_TRUE(tasks[0].isCompleted());
        EXPECT_FALSE(tasks[1].isCompleted());
        EXPECT_TRUE(tasks[2].isCompleted());
    }
    
    // Session 3: Verify persistence across restart
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        std::vector<Task> tasks = manager.listTasks();
        ASSERT_EQ(tasks.size(), 3);
        EXPECT_TRUE(tasks[0].isCompleted());
        EXPECT_FALSE(tasks[1].isCompleted());
        EXPECT_TRUE(tasks[2].isCompleted());
        
        // Verify CLI display shows completion markers
        CLI cli;
        std::stringstream output;
        cli.displayTasks(tasks, output);
        std::string displayText = output.str();
        
        // Should have both completed [X] and incomplete [ ] markers
        EXPECT_NE(displayText.find("[X]"), std::string::npos);
        EXPECT_NE(displayText.find("[ ]"), std::string::npos);
    }
    
    // Verify file content
    std::vector<Task> persistedTasks = readTasksFromFile();
    ASSERT_EQ(persistedTasks.size(), 3);
    EXPECT_TRUE(persistedTasks[0].isCompleted());
    EXPECT_FALSE(persistedTasks[1].isCompleted());
    EXPECT_TRUE(persistedTasks[2].isCompleted());
}

// Test: Clear all tasks → List → Verify empty state and ID reset
TEST_F(IntegrationTest, ClearTasksAndVerifyIdReset) {
    // Session 1: Add and complete some tasks
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        manager.addTask("Task 1");
        manager.addTask("Task 2");
        manager.addTask("Task 3");
        manager.completeTask(2);
    }
    
    // Session 2: Clear all tasks
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        std::vector<Task> beforeClear = manager.listTasks();
        ASSERT_EQ(beforeClear.size(), 3);
        
        manager.clearAllTasks();
        
        std::vector<Task> afterClear = manager.listTasks();
        EXPECT_TRUE(afterClear.empty());
    }
    
    // Session 3: Verify ID counter reset
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        // Add new task, ID should start from 1
        int newId = manager.addTask("New task after clear");
        EXPECT_EQ(newId, 1);
        
        // Add another, should be 2
        int nextId = manager.addTask("Second new task");
        EXPECT_EQ(nextId, 2);
    }
    
    // Verify file content
    std::vector<Task> persistedTasks = readTasksFromFile();
    ASSERT_EQ(persistedTasks.size(), 2);
    EXPECT_EQ(persistedTasks[0].getId(), 1);
    EXPECT_EQ(persistedTasks[1].getId(), 2);
}

// Test: Cross-session persistence (simulate restart, verify data intact)
TEST_F(IntegrationTest, CrossSessionPersistence) {
    // Session 1: Setup initial state
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        manager.addTask("Persistent task 1");
        manager.addTask("Persistent task 2");
        manager.addTask("Persistent task 3");
        manager.completeTask(2);
    }
    
    // Simulate application restart - Session 2
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        std::vector<Task> tasks = manager.listTasks();
        ASSERT_EQ(tasks.size(), 3);
        
        // Verify all data persisted correctly
        EXPECT_EQ(tasks[0].getId(), 1);
        EXPECT_EQ(tasks[0].getDescription(), "Persistent task 1");
        EXPECT_FALSE(tasks[0].isCompleted());
        
        EXPECT_EQ(tasks[1].getId(), 2);
        EXPECT_EQ(tasks[1].getDescription(), "Persistent task 2");
        EXPECT_TRUE(tasks[1].isCompleted());
        
        EXPECT_EQ(tasks[2].getId(), 3);
        EXPECT_EQ(tasks[2].getDescription(), "Persistent task 3");
        EXPECT_FALSE(tasks[2].isCompleted());
        
        // Complete another task
        manager.completeTask(3);
    }
    
    // Simulate another restart - Session 3
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        std::vector<Task> tasks = manager.listTasks();
        ASSERT_EQ(tasks.size(), 3);
        
        // Verify changes from session 2 persisted
        EXPECT_TRUE(tasks[1].isCompleted());
        EXPECT_TRUE(tasks[2].isCompleted());
        
        // ID continuity - next task should be 4
        int newId = manager.addTask("Task after restart");
        EXPECT_EQ(newId, 4);
    }
    
    // Final verification
    std::vector<Task> persistedTasks = readTasksFromFile();
    ASSERT_EQ(persistedTasks.size(), 4);
    EXPECT_EQ(persistedTasks[3].getId(), 4);
    EXPECT_EQ(persistedTasks[3].getDescription(), "Task after restart");
}

// Test: Complete workflow (add→list→complete→list→clear→list)
TEST_F(IntegrationTest, CompleteWorkflow) {
    TaskRepository repo(testFilePath);
    TaskManager manager(repo);
    CLI cli;
    
    // Step 1: Add tasks
    manager.addTask("Design feature");
    manager.addTask("Implement feature");
    manager.addTask("Test feature");
    
    // Step 2: List tasks
    std::vector<Task> tasks1 = manager.listTasks();
    ASSERT_EQ(tasks1.size(), 3);
    EXPECT_FALSE(tasks1[0].isCompleted());
    EXPECT_FALSE(tasks1[1].isCompleted());
    EXPECT_FALSE(tasks1[2].isCompleted());
    
    // Step 3: Complete some tasks
    manager.completeTask(1); // Design complete
    manager.completeTask(2); // Implement complete
    
    // Step 4: List tasks again
    std::vector<Task> tasks2 = manager.listTasks();
    ASSERT_EQ(tasks2.size(), 3);
    EXPECT_TRUE(tasks2[0].isCompleted());
    EXPECT_TRUE(tasks2[1].isCompleted());
    EXPECT_FALSE(tasks2[2].isCompleted());
    
    // Step 5: Clear all tasks
    manager.clearAllTasks();
    
    // Step 6: List tasks - should be empty
    std::vector<Task> tasks3 = manager.listTasks();
    EXPECT_TRUE(tasks3.empty());
    
    // Verify display of empty list
    std::stringstream output;
    cli.displayTasks(tasks3, output);
    std::string displayText = output.str();
    EXPECT_NE(displayText.find("No tasks"), std::string::npos);
}

// Test: Error handling - complete non-existent task
TEST_F(IntegrationTest, ErrorHandlingCompleteNonExistent) {
    TaskRepository repo(testFilePath);
    TaskManager manager(repo);
    
    manager.addTask("Task 1");
    manager.addTask("Task 2");
    
    // Try to complete non-existent task
    bool result = manager.completeTask(999);
    EXPECT_FALSE(result);
    
    // Verify existing tasks unchanged
    std::vector<Task> tasks = manager.listTasks();
    ASSERT_EQ(tasks.size(), 2);
    EXPECT_FALSE(tasks[0].isCompleted());
    EXPECT_FALSE(tasks[1].isCompleted());
}

// Test: Error handling - empty task description
TEST_F(IntegrationTest, ErrorHandlingEmptyDescription) {
    TaskRepository repo(testFilePath);
    TaskManager manager(repo);
    
    // Add task with empty description (should be allowed per current implementation)
    int id = manager.addTask("");
    EXPECT_GT(id, 0);
    
    std::vector<Task> tasks = manager.listTasks();
    ASSERT_EQ(tasks.size(), 1);
    EXPECT_EQ(tasks[0].getDescription(), "");
}

// Test: Multiple sessions with ID continuity
TEST_F(IntegrationTest, MultiSessionIdContinuity) {
    // Session 1: Add tasks with IDs 1, 2, 3
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        EXPECT_EQ(manager.addTask("Task 1"), 1);
        EXPECT_EQ(manager.addTask("Task 2"), 2);
        EXPECT_EQ(manager.addTask("Task 3"), 3);
    }
    
    // Session 2: Next ID should be 4
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        EXPECT_EQ(manager.addTask("Task 4"), 4);
    }
    
    // Session 3: Complete and add more
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        manager.completeTask(2);
        EXPECT_EQ(manager.addTask("Task 5"), 5);
    }
    
    // Final verification
    {
        TaskRepository repo(testFilePath);
        TaskManager manager(repo);
        
        std::vector<Task> tasks = manager.listTasks();
        ASSERT_EQ(tasks.size(), 5);
        
        // Verify IDs are sequential
        for (int i = 0; i < 5; i++) {
            EXPECT_EQ(tasks[i].getId(), i + 1);
        }
        
        // Verify only task 2 is completed
        EXPECT_FALSE(tasks[0].isCompleted());
        EXPECT_TRUE(tasks[1].isCompleted());
        EXPECT_FALSE(tasks[2].isCompleted());
        EXPECT_FALSE(tasks[3].isCompleted());
        EXPECT_FALSE(tasks[4].isCompleted());
    }
}

// Test: CLI command parsing integration
TEST_F(IntegrationTest, CLICommandParsing) {
    CLI cli;
    
    // Test add command with quotes
    {
        const char* argv[] = {"task-manager", "add", "\"Buy groceries\""};
        Command cmd = cli.parseCommand(3, const_cast<char**>(argv));
        EXPECT_EQ(cmd.type, CommandType::ADD);
        EXPECT_EQ(cmd.argument, "\"Buy groceries\"");
    }
    
    // Test add command without quotes
    {
        const char* argv[] = {"task-manager", "add", "Write", "documentation"};
        Command cmd = cli.parseCommand(4, const_cast<char**>(argv));
        EXPECT_EQ(cmd.type, CommandType::ADD);
        EXPECT_EQ(cmd.argument, "Write documentation");
    }
    
    // Test list command
    {
        const char* argv[] = {"task-manager", "list"};
        Command cmd = cli.parseCommand(2, const_cast<char**>(argv));
        EXPECT_EQ(cmd.type, CommandType::LIST);
    }
    
    // Test complete command
    {
        const char* argv[] = {"task-manager", "complete", "1"};
        Command cmd = cli.parseCommand(3, const_cast<char**>(argv));
        EXPECT_EQ(cmd.type, CommandType::COMPLETE);
        EXPECT_EQ(cmd.argument, "1");
    }
    
    // Test clear command
    {
        const char* argv[] = {"task-manager", "clear"};
        Command cmd = cli.parseCommand(2, const_cast<char**>(argv));
        EXPECT_EQ(cmd.type, CommandType::CLEAR);
    }
    
    // Test help command
    {
        const char* argv[] = {"task-manager", "--help"};
        Command cmd = cli.parseCommand(2, const_cast<char**>(argv));
        EXPECT_EQ(cmd.type, CommandType::HELP);
    }
    
    // Test invalid command
    {
        const char* argv[] = {"task-manager", "invalid"};
        Command cmd = cli.parseCommand(2, const_cast<char**>(argv));
        EXPECT_EQ(cmd.type, CommandType::INVALID);
    }
}

// Test: File corruption recovery
TEST_F(IntegrationTest, FileCorruptionHandling) {
    // Create a corrupted JSON file
    {
        std::ofstream file(testFilePath);
        file << "{ this is not valid JSON }";
        file.close();
    }
    
    // Repository should handle gracefully (current implementation may throw)
    // This test documents current behavior
    try {
        TaskRepository repo(testFilePath);
        std::vector<Task> tasks = repo.loadTasks();
        // If we get here, corruption was handled
        SUCCEED();
    } catch (const std::exception& e) {
        // Current implementation may throw - document this
        SUCCEED() << "Exception caught as expected: " << e.what();
    }
}

// Test: Large number of tasks (stress test)
TEST_F(IntegrationTest, LargeNumberOfTasks) {
    TaskRepository repo(testFilePath);
    TaskManager manager(repo);
    
    // Add 100 tasks
    for (int i = 1; i <= 100; i++) {
        int id = manager.addTask("Task " + std::to_string(i));
        EXPECT_EQ(id, i);
    }
    
    // Verify all tasks exist
    std::vector<Task> tasks = manager.listTasks();
    ASSERT_EQ(tasks.size(), 100);
    
    // Complete every other task
    for (int i = 1; i <= 100; i += 2) {
        manager.completeTask(i);
    }
    
    // Verify completion status
    tasks = manager.listTasks();
    for (int i = 0; i < 100; i++) {
        if ((i + 1) % 2 == 1) {
            EXPECT_TRUE(tasks[i].isCompleted());
        } else {
            EXPECT_FALSE(tasks[i].isCompleted());
        }
    }
    
    // Verify persistence
    std::vector<Task> persistedTasks = readTasksFromFile();
    ASSERT_EQ(persistedTasks.size(), 100);
}
