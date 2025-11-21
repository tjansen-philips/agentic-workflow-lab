# Task Manager CLI - Architecture and Design

## System Overview

The Task Manager CLI is a single-executable command-line application built in C++ with a layered architecture that separates concerns between presentation, business logic, and data persistence.

## High-Level Architecture

```
┌─────────────────────────────────────┐
│         CLI Interface Layer         │
│  (main.cpp - User Interaction)      │
└─────────────┬───────────────────────┘
              │
              ▼
┌─────────────────────────────────────┐
│      Business Logic Layer           │
│  (TaskManager - Core Operations)    │
└─────────────┬───────────────────────┘
              │
              ▼
┌─────────────────────────────────────┐
│      Data Persistence Layer         │
│  (FileStorage - Load/Save Tasks)    │
└─────────────────────────────────────┘
```

## Component Design

### 1. CLI Interface (main.cpp)

**Responsibility**: Handle user input, display output, coordinate application flow

**Key Functions**:
- Parse command-line arguments
- Display menu and help information
- Route commands to TaskManager
- Format and display results to user

**Design Considerations**:
- Keep minimal business logic in this layer
- Focus on input validation and output formatting
- Use clear, consistent command structure

### 2. TaskManager Class

**Responsibility**: Implement core task management operations

**Key Methods**:
- `addTask(description, priority)` - Create new task
- `listTasks()` - Retrieve all tasks
- `completeTask(id)` - Mark task as complete
- `deleteTask(id)` - Remove task
- `loadTasks()` - Initialize from storage
- `saveTasks()` - Persist to storage

**Design Considerations**:
- Maintain in-memory collection of tasks
- Automatically save after each modification
- Generate unique task IDs
- Validate operations (e.g., task exists)

### 3. Task Data Structure

**Responsibility**: Represent a single task

**Properties**:
- `id` (int) - Unique identifier
- `description` (string) - Task description
- `priority` (enum: LOW, MEDIUM, HIGH)
- `completed` (bool) - Completion status

**Design Considerations**:
- Simple POD (Plain Old Data) structure
- Easy to serialize/deserialize
- Lightweight for efficient memory usage

### 4. FileStorage Class

**Responsibility**: Handle file I/O for task persistence

**Key Methods**:
- `loadTasks(filename)` - Read tasks from file
- `saveTasks(filename, tasks)` - Write tasks to file

**File Format**:
```
id|description|priority|completed
1|Implement file storage|HIGH|false
2|Add unit tests|MEDIUM|false
```

**Design Considerations**:
- Use simple delimited text format (pipe-separated)
- Handle file not found gracefully
- Create file if it doesn't exist
- Use atomic writes to prevent corruption

## Design Patterns

### Layered Architecture
- Clear separation between presentation, business logic, and data
- Each layer depends only on the layer below it
- Easy to test and modify independently

### Repository Pattern (FileStorage)
- Abstract data persistence details
- Easy to swap storage implementations later
- Centralize file I/O error handling

## Data Flow

### Adding a Task
1. User enters command: `task-manager add "Fix bug" high`
2. CLI parses arguments and validates input
3. CLI calls `taskManager.addTask("Fix bug", HIGH)`
4. TaskManager creates Task with unique ID
5. TaskManager adds to in-memory collection
6. TaskManager calls `fileStorage.saveTasks()`
7. FileStorage writes all tasks to file
8. CLI displays success message

### Listing Tasks
1. User enters command: `task-manager list`
2. CLI calls `taskManager.listTasks()`
3. TaskManager returns vector of tasks
4. CLI formats and displays tasks in table format

## Build System

**Build Tool**: GNU Make

**Build Targets**:
- `make` or `make all` - Build the executable
- `make clean` - Remove compiled files
- `make test` - Run tests (if implemented)

**Compiler Flags**:
- `-std=c++17` - Use C++17 standard
- `-Wall -Wextra` - Enable all warnings
- `-O2` - Optimization level 2 for release builds

## File Structure

```
agentic-workflow-lab/
├── src/
│   ├── main.cpp           # CLI interface
│   ├── TaskManager.h      # Business logic header
│   ├── TaskManager.cpp    # Business logic implementation
│   ├── FileStorage.h      # Persistence header
│   ├── FileStorage.cpp    # Persistence implementation
│   └── Task.h             # Task data structure
├── Makefile               # Build configuration
├── tasks.txt              # Task data file (created at runtime)
└── [documentation files]
```

## Error Handling

- Use return codes for error conditions
- Validate all user inputs before processing
- Handle file I/O errors gracefully
- Provide clear error messages to users
- Never crash on bad input

## Testing Strategy

- Unit tests for TaskManager operations
- File I/O tests for FileStorage
- Integration tests for complete workflows
- Manual testing for CLI interactions

## Performance Considerations

- In-memory operations for fast access
- Batch save operations to minimize I/O
- Simple file format for quick parsing
- Expected capacity: hundreds of tasks (not thousands)

## Security Considerations

- No authentication required (single-user, local)
- Validate file paths to prevent directory traversal
- Handle file permissions appropriately
- No sensitive data stored

## Future Architecture Extensions

- Add abstraction layer for different storage backends
- Implement observer pattern for UI updates
- Add command pattern for undo/redo functionality
- Consider SQLite for better query capabilities
