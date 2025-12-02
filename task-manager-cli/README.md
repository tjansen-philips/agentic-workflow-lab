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

**Total: 41 tests with 100% pass rate**

### Running Specific Tests

```powershell
# Run only Task tests
.\build\Debug\task-manager-tests.exe --gtest_filter=TaskTest.*

# Run only TaskManager tests
.\build\Debug\task-manager-tests.exe --gtest_filter=TaskManagerTest.*
```

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
│   └── test_cli.cpp
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
