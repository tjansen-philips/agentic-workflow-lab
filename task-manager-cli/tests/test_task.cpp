#include <gtest/gtest.h>
#include "task.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Test task creation with all parameters
TEST(TaskTest, CreateTask) {
    Task task(1, "Buy groceries", false);
    
    EXPECT_EQ(task.getId(), 1);
    EXPECT_EQ(task.getDescription(), "Buy groceries");
    EXPECT_FALSE(task.isCompleted());
}

// Test task creation with completed status
TEST(TaskTest, CreateCompletedTask) {
    Task task(2, "Complete project", true);
    
    EXPECT_EQ(task.getId(), 2);
    EXPECT_EQ(task.getDescription(), "Complete project");
    EXPECT_TRUE(task.isCompleted());
}

// Test setting task as completed
TEST(TaskTest, SetCompleted) {
    Task task(1, "Test task", false);
    EXPECT_FALSE(task.isCompleted());
    
    task.setCompleted(true);
    EXPECT_TRUE(task.isCompleted());
    
    task.setCompleted(false);
    EXPECT_FALSE(task.isCompleted());
}

// Test JSON serialization
TEST(TaskTest, ToJson) {
    Task task(5, "Write tests", true);
    json j = task.toJson();
    
    EXPECT_EQ(j["id"], 5);
    EXPECT_EQ(j["description"], "Write tests");
    EXPECT_EQ(j["completed"], true);
}

// Test JSON deserialization
TEST(TaskTest, FromJson) {
    json j = {
        {"id", 10},
        {"description", "Review code"},
        {"completed", false}
    };
    
    Task task = Task::fromJson(j);
    
    EXPECT_EQ(task.getId(), 10);
    EXPECT_EQ(task.getDescription(), "Review code");
    EXPECT_FALSE(task.isCompleted());
}

// Test JSON round-trip (serialize then deserialize)
TEST(TaskTest, JsonRoundTrip) {
    Task original(42, "Round trip test", true);
    json j = original.toJson();
    Task restored = Task::fromJson(j);
    
    EXPECT_EQ(restored.getId(), original.getId());
    EXPECT_EQ(restored.getDescription(), original.getDescription());
    EXPECT_EQ(restored.isCompleted(), original.isCompleted());
}
