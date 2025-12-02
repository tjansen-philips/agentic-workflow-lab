# Task Manager CLI - Architecture and Design

## System Overview

The Task Manager CLI is a single-executable command-line application with a layered architecture that separates concerns between presentation, business logic, and data persistence. Built in C++17 with test-driven development, featuring comprehensive unit tests (41 tests total).

## Implementation Details

### Language and Standards
- **Language**: C++17
- **Build System**: CMake 3.15+
- **Testing Framework**: Google Test
- **JSON Library**: nlohmann/json (header-only)
- **Persistence**: JSON file storage in executable directory

### Commands Implemented
1. `add <description>` - Create new task
2. `list` - Display all tasks with completion status
3. `complete <id>` - Mark task as completed
4. `clear` - Remove all tasks and reset ID counter
5. `--help` - Display usage information

## Design Patterns

### Layered Architecture
- **Presentation Layer**: CLI parsing and display (cli.h/cpp, main.cpp)
- **Business Logic Layer**: Task management operations (task_manager.h/cpp, task.h/cpp)
- **Data Layer**: File persistence and JSON serialization (task_repository.h/cpp)
- Each layer depends only on the layer below it
- Easy to test and modify independently

### Repository Pattern 
- Abstract data persistence details
- TaskRepository handles all file I/O operations
- ID counter management centralized in repository
- Easy to swap storage implementations later

### Dependency Injection
- TaskManager receives TaskRepository reference via constructor
- Enables isolated unit testing with mock repositories
- Promotes loose coupling between components

## Security Considerations
- No authentication required (single-user, local)
- File operations restricted to executable directory
- Input validation at CLI boundary

## Tests
- **Unit Tests**: 41 tests covering all layers (100% pass rate)
  - Task: 6 tests (data model, JSON serialization)
  - TaskRepository: 9 tests (file I/O, ID management, clear functionality)
  - TaskManager: 13 tests (business logic, persistence, clear operations)
  - CLI: 13 tests (command parsing, display, help text)
- **Test-Driven Development**: All features implemented with tests-first approach
- **Continuous Testing**: All tests pass after each implementation phase