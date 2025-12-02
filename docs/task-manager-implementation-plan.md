---
title: Task Manager CLI Implementation Plan
version: 1.0
date_created: 2025-12-02
last_updated: 2025-12-02
---
# Implementation Plan: Task Manager CLI (C++)

Create a minimal Task Manager CLI application in C++ for demo purposes. The application will support three core operations: adding tasks, listing tasks, and marking tasks as complete. Data will be persisted to a JSON file in the executable directory. The implementation follows a layered architecture with clear separation between presentation (CLI), business logic (task management), and data persistence.

## Architecture and design

### High-Level Architecture

The application follows a **layered architecture pattern**:

1. **Presentation Layer** (`main.cpp`, `cli.h/cpp`)
   - Parses command-line arguments
   - Displays output to console with help text on errors
   - Handles user input/output formatting

2. **Business Logic Layer** (`task_manager.h/cpp`, `task.h/cpp`)
   - Manages task operations (add, list, complete)
   - Enforces business rules
   - Coordinates between CLI and repository

3. **Data Layer** (`task_repository.h/cpp`)
   - Handles file I/O operations
   - Serializes/deserializes tasks to/from JSON
   - Abstracts persistence details using repository pattern

### Data Model

**Task Structure:**
- `id`: Unique integer identifier (auto-incremented, never reused)
- `description`: String describing the task
- `completed`: Boolean status flag

**Storage Format:**
- JSON file (`tasks.json`) stored in executable directory
- Simple array structure for easy parsing
- Uses `std::filesystem` to determine executable path

### Technology Stack

- **Language:** C++17 (modern features, widely supported)
- **Build System:** CMake 3.15+
- **JSON Library:** nlohmann/json (header-only, simple API)
- **Testing Framework:** Google Test (gtest)
- **Compiler:** MSVC/GCC/Clang compatible

### Design Patterns

- **Repository Pattern:** Abstract data persistence
- **Dependency Injection:** Pass repository to manager for testability
- **Single Responsibility:** Each class has one clear purpose

### User Experience Decisions

✅ **Error Handling:** Display help text for invalid commands or malformed input  
✅ **Task ID Display:** Show original IDs (may have gaps, consistent with complete command)  
✅ **JSON File Location:** Store in executable directory using `std::filesystem`

## Tasks

### Phase 1: Project Setup and Structure

- [x] Create `/task-manager-cli` directory structure
- [x] Create root `CMakeLists.txt` with C++17 configuration
- [x] Download and integrate nlohmann/json library
- [x] Set up Google Test framework via CMake FetchContent

### Phase 2: Data Model and Persistence Layer

- [x] Implement `Task` class (`task.h/cpp`)
  - Constructor with id, description, completed status
  - Getters for all properties
  - `setCompleted()` method
  - `toJson()` and `fromJson()` serialization methods

- [x] Implement `TaskRepository` class (`task_repository.h/cpp`)
  - `loadTasks()`: Read tasks from JSON file
  - `saveTasks()`: Write tasks to JSON file
  - `getNextId()`: Generate unique IDs
  - Error handling for file I/O

- [x] Write unit tests for `Task` (6 tests)
- [x] Write unit tests for `TaskRepository` (7 tests)

### Phase 3: Business Logic Layer

- [x] Implement `TaskManager` class (`task_manager.h/cpp`)
  - Constructor accepting `TaskRepository&` reference
  - `addTask(description)`: Create and persist new task
  - `listTasks()`: Return all tasks
  - `completeTask(id)`: Mark task as completed

- [x] Write unit tests for `TaskManager` (9 tests)

### Phase 4: Presentation Layer (CLI)

- [x] Implement `CLI` class (`cli.h/cpp`)
  - `parseCommand(argc, argv)`: Parse command-line arguments
  - `displayHelp()`: Print usage instructions
  - `displayTasks(tasks)`: Format and print task list with original IDs
  - `displaySuccess(message)`: Print success messages
  - `displayError(message)`: Print error messages followed by help text
  - Support commands: `add`, `list`, `complete`, `--help`

- [x] Implement `main.cpp`
  - Initialize TaskRepository and TaskManager
  - Parse arguments and dispatch to appropriate methods
  - Handle errors with help display
  - Return appropriate exit codes

- [x] Write unit tests for CLI (12 tests)

### Phase 5: Documentation and Build Verification

- [x] Create `/task-manager-cli/README.md`
- [x] Update `/docs/CONTRIBUTING.md` with C++ coding standards
- [x] Verify build and test execution (34 tests, 100% pass rate)
- [x] Test executable manually with all commands

## Implementation Status

**✅ ALL TASKS COMPLETED**

- Total tests: 34
- Pass rate: 100%
- Build system: CMake with Google Test integration
- Documentation: Complete with usage examples
- Test-driven development: All components implemented following TDD principles

## Open questions

~~All questions have been resolved:~~

1. ✅ **Error Handling Strategy**: Display help text when commands are malformed or invalid
2. ✅ **Task ID Display**: Show original IDs (preserves gaps, consistent with complete command)
3. ✅ **JSON File Location**: Store in executable directory using `std::filesystem`
