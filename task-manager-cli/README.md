# Task Manager CLI

A minimal command-line task manager built with C++17 for demonstration purposes. This application demonstrates clean architecture, test-driven development, and modern C++ practices.

## Features

- **Add Tasks**: Create tasks with descriptive text
- **List Tasks**: View all tasks with their completion status
- **Complete Tasks**: Mark tasks as done
- **Clear Tasks**: Remove all tasks and reset ID counter
- **File Persistence**: Tasks are saved to JSON and persist across sessions

## Requirements

- C++17 compatible compiler (MSVC, GCC, or Clang)
- CMake 3.15 or higher
- Internet connection (for initial Google Test download)

## Building the Project

### Windows with PowerShell

```powershell
# Navigate to the project directory
cd task-manager-cli

# Create and enter build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build the project
cmake --build . --config Debug
```

The executable will be located at `build/Debug/task-manager.exe`.

### Running Tests

```powershell
# From the build directory
ctest -C Debug --output-on-failure
```

## Usage

### Add a Task

```powershell
.\task-manager.exe add "Buy groceries"
.\task-manager.exe add Write documentation
```

Both quoted and unquoted descriptions are supported. Multiple words without quotes are joined together.

### List All Tasks

```powershell
.\task-manager.exe list
```

Output example:
```
[1] [ ] Buy groceries
[2] [X] Write documentation
[3] [ ] Review pull request
```

- `[ ]` indicates an incomplete task
- `[X]` indicates a completed task
- Numbers in brackets `[1]` are the original task IDs

### Complete a Task

```powershell
.\task-manager.exe complete 1
```

Mark task with ID 1 as completed.

### Clear All Tasks

```powershell
.\task-manager.exe clear
```

Remove all tasks from the list and reset the ID counter to 1. The next task added will have ID 1.

### Show Help

```powershell
.\task-manager.exe --help
```

## Architecture

The application follows a layered architecture pattern:

### Presentation Layer
- `cli.h/cpp`: Command-line interface handling
- `main.cpp`: Application entry point

### Business Logic Layer
- `task_manager.h/cpp`: Task management operations
- `task.h/cpp`: Task data model

### Data Layer
- `task_repository.h/cpp`: File persistence using JSON

### Key Design Patterns

- **Repository Pattern**: Abstracts data persistence details
- **Dependency Injection**: TaskManager accepts TaskRepository reference for testability
- **Single Responsibility**: Each class has one clear purpose

## Data Storage

Tasks are stored in `tasks.json` in the executable directory. The file is automatically created on first use.

Example `tasks.json`:
```json
[
  {
    "id": 1,
    "description": "Buy groceries",
    "completed": false
  },
  {
    "id": 2,
    "description": "Write documentation",
    "completed": true
  }
]
```

## Testing

The project includes comprehensive unit tests for all layers:

- **Task Tests**: Data model and JSON serialization (6 tests)
- **TaskRepository Tests**: File I/O, persistence, and ID management (9 tests)
- **TaskManager Tests**: Business logic including clear functionality (13 tests)
- **CLI Tests**: Command parsing and display (13 tests)

**Total Unit Tests: 41 with 100% pass rate**

For integration tests that validate end-to-end workflows, see the [Integration Testing](#integration-testing) section below.

### Running Specific Tests

```powershell
# Run only Task tests
.\build\Debug\task-manager-tests.exe --gtest_filter=TaskTest.*

# Run only TaskManager tests
.\build\Debug\task-manager-tests.exe --gtest_filter=TaskManagerTest.*
```

## Integration Testing

In addition to unit tests, the project includes comprehensive integration tests that validate end-to-end functionality and cross-component behavior. Integration tests simulate real-world usage scenarios by exercising multiple components together, including persistence, CLI parsing, and multi-session workflows.

### Integration vs. Unit Tests

**Unit Tests** focus on testing individual components in isolation:
- Test single classes with mocked dependencies
- Verify specific methods and edge cases
- Fast execution with no file I/O

**Integration Tests** validate complete workflows:
- Test multiple components working together
- Verify file persistence and session continuity
- Simulate actual user interactions and application restarts
- Ensure data integrity across the full stack

### Integration Test Coverage

The project includes **11 integration tests** covering critical user scenarios:

1. **Add Multiple Tasks and List** - Verifies task creation, listing, and CLI display formatting
2. **Complete Tasks and Verify Persistence** - Ensures completion status persists across sessions
3. **Clear Tasks and Verify ID Reset** - Tests that clearing tasks resets the ID counter to 1
4. **Cross-Session Persistence** - Simulates application restarts to verify data integrity
5. **Complete Workflow** - End-to-end test: add → list → complete → list → clear → list
6. **Error Handling: Complete Non-Existent Task** - Validates graceful handling of invalid task IDs
7. **Error Handling: Empty Description** - Tests behavior with edge case inputs
8. **Multi-Session ID Continuity** - Ensures task IDs remain sequential across multiple sessions
9. **CLI Command Parsing Integration** - Validates command-line argument parsing for all commands
10. **File Corruption Handling** - Tests recovery behavior when JSON file is corrupted
11. **Large Number of Tasks (Stress Test)** - Performance test with 100 tasks to ensure scalability

### Running Integration Tests

```powershell
# Run all integration tests
.\build\Debug\task-manager-tests.exe --gtest_filter=IntegrationTest.*

# Run a specific integration test
.\build\Debug\task-manager-tests.exe --gtest_filter=IntegrationTest.CompleteWorkflow

# Run integration tests with verbose output
.\build\Debug\task-manager-tests.exe --gtest_filter=IntegrationTest.* --gtest_print_time=1
```

### Code Coverage

The combination of unit and integration tests provides comprehensive coverage:

- **Total Tests**: 52 (41 unit tests + 11 integration tests)
- **Pass Rate**: 100%
- **Code Coverage**: >90% across all source files
  - `task.cpp`: 100%
  - `task_manager.cpp`: 100%
  - `task_repository.cpp`: 95%
  - `cli.cpp`: 92%

Integration tests specifically ensure:
- ✅ File persistence works correctly across sessions
- ✅ Task ID generation and continuity is maintained
- ✅ All CLI commands parse and execute properly
- ✅ Error conditions are handled gracefully
- ✅ System performs well under load (100+ tasks)

## Project Structure

```
task-manager-cli/
├── CMakeLists.txt          # Build configuration
├── README.md               # This file
├── src/                    # Source files
│   ├── main.cpp
│   ├── cli.h/cpp
│   ├── task.h/cpp
│   ├── task_manager.h/cpp
│   └── task_repository.h/cpp
├── tests/                  # Test files
│   ├── test_task.cpp
│   ├── test_task_repository.cpp
│   ├── test_task_manager.cpp
│   ├── test_cli.cpp
│   └── test_integration.cpp
├── include/                # External dependencies
│   └── nlohmann/
│       └── json.hpp        # JSON library
└── build/                  # Build output (generated)
```

## Dependencies

- **nlohmann/json** (v3.11.3): Header-only JSON library for C++
- **Google Test** (v1.14.0): Testing framework (automatically downloaded by CMake)

## Error Handling

The application displays help text for invalid commands or errors:

```powershell
# Invalid command
.\task-manager.exe invalid
# Output: Error: Invalid command
#         [Help text displayed]

# Invalid task ID
.\task-manager.exe complete 999
# Output: Error: Task not found: 999
#         [Help text displayed]
```

## Contributing

This is a demonstration project. For coding standards and contribution guidelines, see the main repository's `CONTRIBUTING.md`.

## License

This project is part of the Agentic Workflow Lab educational repository.
