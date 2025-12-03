#include <gtest/gtest.h>
#include "file_task_repository.h"
#include "repository_exceptions.h"
#include "task.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class ErrorHandlingTest : public ::testing::Test {
protected:
    std::string testFilePath;
    
    void SetUp() override {
        testFilePath = "error_test_tasks.json";
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

// Test corrupted JSON file - invalid JSON syntax
TEST_F(ErrorHandlingTest, CorruptedJsonInvalidSyntax) {
    // Create a file with invalid JSON
    std::ofstream file(testFilePath);
    file << "{ this is not valid json }";
    file.close();
    
    FileTaskRepository repo(testFilePath);
    
    EXPECT_THROW({
        repo.loadTasks();
    }, JsonParseException);
}

// Test corrupted JSON file - valid JSON but not an array
TEST_F(ErrorHandlingTest, CorruptedJsonNotArray) {
    // Create a file with valid JSON but not an array
    std::ofstream file(testFilePath);
    file << R"({"id": 1, "description": "test", "completed": false})";
    file.close();
    
    FileTaskRepository repo(testFilePath);
    
    EXPECT_THROW({
        repo.loadTasks();
    }, JsonParseException);
}

// Test corrupted JSON file - incomplete JSON
TEST_F(ErrorHandlingTest, CorruptedJsonIncomplete) {
    // Create a file with incomplete JSON
    std::ofstream file(testFilePath);
    file << R"([{"id": 1, "description": "test")";
    file.close();
    
    FileTaskRepository repo(testFilePath);
    
    EXPECT_THROW({
        repo.loadTasks();
    }, JsonParseException);
}

// Test corrupted JSON file - empty file
TEST_F(ErrorHandlingTest, EmptyJsonFile) {
    // Create an empty file
    std::ofstream file(testFilePath);
    file.close();
    
    FileTaskRepository repo(testFilePath);
    
    EXPECT_THROW({
        repo.loadTasks();
    }, JsonParseException);
}

// Test invalid file path (directory instead of file)
TEST_F(ErrorHandlingTest, InvalidFilePathDirectory) {
    std::string dirPath = "test_directory_not_file";
    
    // Create a directory
    fs::create_directory(dirPath);
    
    FileTaskRepository repo(dirPath);
    
    // Should throw when trying to load from a directory
    EXPECT_THROW({
        repo.loadTasks();
    }, FileIOException);
    
    // Clean up
    fs::remove(dirPath);
}

// Test read-only file system simulation (cannot test actual permissions on all platforms)
TEST_F(ErrorHandlingTest, CannotCreateFile) {
    // Use an invalid path that cannot be created
    std::string invalidPath = "/nonexistent/path/that/does/not/exist/tasks.json";
    
    FileTaskRepository repo(invalidPath);
    
    // Should throw when trying to create file in non-existent directory
    EXPECT_THROW({
        repo.loadTasks();
    }, FileIOException);
}

// Test save to invalid path
TEST_F(ErrorHandlingTest, SaveToInvalidPath) {
    std::string invalidPath = "/nonexistent/path/that/does/not/exist/tasks.json";
    
    FileTaskRepository repo(invalidPath);
    std::vector<Task> tasks = {Task(1, "Test task", false)};
    
    // Should throw when trying to save to non-existent directory
    EXPECT_THROW({
        repo.saveTasks(tasks);
    }, FileIOException);
}

// Test JSON with missing required fields
TEST_F(ErrorHandlingTest, JsonMissingRequiredFields) {
    // Create a file with JSON missing required task fields
    std::ofstream file(testFilePath);
    file << R"([{"id": 1, "completed": false}])"; // Missing "description"
    file.close();
    
    FileTaskRepository repo(testFilePath);
    
    // Should throw JsonParseException when parsing task with missing field
    EXPECT_THROW({
        repo.loadTasks();
    }, JsonParseException);
}

// Test successful recovery after fixing corrupted file
TEST_F(ErrorHandlingTest, RecoveryAfterFixingCorruptedFile) {
    FileTaskRepository repo(testFilePath);
    
    // Create corrupted file
    std::ofstream badFile(testFilePath);
    badFile << "{ invalid }";
    badFile.close();
    
    // Should throw on corrupted file
    EXPECT_THROW({
        repo.loadTasks();
    }, JsonParseException);
    
    // Fix the file
    std::ofstream goodFile(testFilePath);
    goodFile << R"([{"id": 1, "description": "Fixed task", "completed": false}])";
    goodFile.close();
    
    // Should now work
    std::vector<Task> tasks;
    EXPECT_NO_THROW({
        tasks = repo.loadTasks();
    });
    
    ASSERT_EQ(tasks.size(), 1);
    EXPECT_EQ(tasks[0].getDescription(), "Fixed task");
}

// Test exception message contains useful context
TEST_F(ErrorHandlingTest, ExceptionMessageContainsContext) {
    // Create a file with invalid JSON
    std::ofstream file(testFilePath);
    file << "invalid json content";
    file.close();
    
    FileTaskRepository repo(testFilePath);
    
    try {
        repo.loadTasks();
        FAIL() << "Expected JsonParseException";
    } catch (const JsonParseException& e) {
        std::string message = e.what();
        // Check that error message contains useful context
        EXPECT_TRUE(message.find("JSON") != std::string::npos);
        EXPECT_TRUE(message.find("parse") != std::string::npos || 
                    message.find("parsing") != std::string::npos);
    }
}

// Test that FileIOException is thrown for file operations
TEST_F(ErrorHandlingTest, FileIOExceptionForInvalidPath) {
    std::string invalidPath = "/this/path/does/not/exist/file.json";
    FileTaskRepository repo(invalidPath);
    
    try {
        repo.loadTasks();
        FAIL() << "Expected FileIOException";
    } catch (const FileIOException& e) {
        std::string message = e.what();
        // Check that error message contains useful context
        EXPECT_TRUE(message.find("File") != std::string::npos || 
                    message.find("file") != std::string::npos);
    }
}
