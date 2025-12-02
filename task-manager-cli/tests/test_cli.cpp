#include <gtest/gtest.h>
#include "cli.h"
#include <sstream>
#include <vector>

// Test parsing add command with quotes
TEST(CLITest, ParseAddCommandWithQuotes) {
    const char* argv[] = {"task-manager", "add", "Buy groceries"};
    CLI cli;
    
    auto cmd = cli.parseCommand(3, const_cast<char**>(argv));
    
    EXPECT_EQ(cmd.type, CommandType::ADD);
    EXPECT_EQ(cmd.argument, "Buy groceries");
}

// Test parsing add command without quotes
TEST(CLITest, ParseAddCommandMultipleWords) {
    const char* argv[] = {"task-manager", "add", "Buy", "some", "groceries"};
    CLI cli;
    
    auto cmd = cli.parseCommand(5, const_cast<char**>(argv));
    
    EXPECT_EQ(cmd.type, CommandType::ADD);
    EXPECT_EQ(cmd.argument, "Buy some groceries");
}

// Test parsing list command
TEST(CLITest, ParseListCommand) {
    const char* argv[] = {"task-manager", "list"};
    CLI cli;
    
    auto cmd = cli.parseCommand(2, const_cast<char**>(argv));
    
    EXPECT_EQ(cmd.type, CommandType::LIST);
}

// Test parsing complete command
TEST(CLITest, ParseCompleteCommand) {
    const char* argv[] = {"task-manager", "complete", "5"};
    CLI cli;
    
    auto cmd = cli.parseCommand(3, const_cast<char**>(argv));
    
    EXPECT_EQ(cmd.type, CommandType::COMPLETE);
    EXPECT_EQ(cmd.argument, "5");
}

// Test parsing help command
TEST(CLITest, ParseHelpCommand) {
    const char* argv[] = {"task-manager", "--help"};
    CLI cli;
    
    auto cmd = cli.parseCommand(2, const_cast<char**>(argv));
    
    EXPECT_EQ(cmd.type, CommandType::HELP);
}

// Test parsing invalid command
TEST(CLITest, ParseInvalidCommand) {
    const char* argv[] = {"task-manager", "invalid"};
    CLI cli;
    
    auto cmd = cli.parseCommand(2, const_cast<char**>(argv));
    
    EXPECT_EQ(cmd.type, CommandType::INVALID);
}

// Test parsing no command
TEST(CLITest, ParseNoCommand) {
    const char* argv[] = {"task-manager"};
    CLI cli;
    
    auto cmd = cli.parseCommand(1, const_cast<char**>(argv));
    
    EXPECT_EQ(cmd.type, CommandType::INVALID);
}

// Test displaying help
TEST(CLITest, DisplayHelp) {
    CLI cli;
    std::stringstream ss;
    
    cli.displayHelp(ss);
    
    std::string output = ss.str();
    EXPECT_TRUE(output.find("Usage:") != std::string::npos);
    EXPECT_TRUE(output.find("add") != std::string::npos);
    EXPECT_TRUE(output.find("list") != std::string::npos);
    EXPECT_TRUE(output.find("complete") != std::string::npos);
}

// Test displaying tasks
TEST(CLITest, DisplayTasks) {
    CLI cli;
    std::stringstream ss;
    
    std::vector<Task> tasks = {
        Task(1, "Buy groceries", false),
        Task(2, "Write code", true),
        Task(5, "Review PR", false)
    };
    
    cli.displayTasks(tasks, ss);
    
    std::string output = ss.str();
    EXPECT_TRUE(output.find("[1]") != std::string::npos);
    EXPECT_TRUE(output.find("Buy groceries") != std::string::npos);
    EXPECT_TRUE(output.find("[2]") != std::string::npos);
    EXPECT_TRUE(output.find("Write code") != std::string::npos);
    EXPECT_TRUE(output.find("[5]") != std::string::npos);
    EXPECT_TRUE(output.find("Review PR") != std::string::npos);
}

// Test displaying empty task list
TEST(CLITest, DisplayEmptyTasks) {
    CLI cli;
    std::stringstream ss;
    
    std::vector<Task> tasks;
    
    cli.displayTasks(tasks, ss);
    
    std::string output = ss.str();
    EXPECT_TRUE(output.find("No tasks") != std::string::npos || output.empty());
}

// Test displaying success message
TEST(CLITest, DisplaySuccess) {
    CLI cli;
    std::stringstream ss;
    
    cli.displaySuccess("Task added successfully", ss);
    
    std::string output = ss.str();
    EXPECT_TRUE(output.find("Task added successfully") != std::string::npos);
}

// Test displaying error message
TEST(CLITest, DisplayError) {
    CLI cli;
    std::stringstream ss;
    
    cli.displayError("Invalid task ID", ss);
    
    std::string output = ss.str();
    EXPECT_TRUE(output.find("Invalid task ID") != std::string::npos);
}
