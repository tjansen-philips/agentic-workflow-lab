# Contributing Guidelines

This document outlines the coding standards and best practices for the Task Manager CLI project.

## Code Style and Standards

### Naming Conventions

- **Classes**: PascalCase (e.g., `TaskManager`, `TaskRepository`)
- **Methods/Functions**: camelCase (e.g., `addTask()`, `loadTasks()`)
- **Variables**: camelCase (e.g., `taskId`, `description`)
- **Constants**: UPPER_SNAKE_CASE (e.g., `MAX_TASKS`)
- **Private members**: camelCase with no prefix (e.g., `repository`, `tasks`)
- **Files**: snake_case matching class names (e.g., `task_manager.h`, `task_manager.cpp`)

### Code Formatting

- **Indentation**: 4 spaces (no tabs)
- **Braces**: Opening brace on same line for functions and control structures
  ```cpp
  void functionName() {
      // code
  }
  ```
- **Line Length**: Aim for 100 characters or less
- **Whitespace**: Space after keywords, around operators, no trailing whitespace

### File Organization

- **Header Files** (`.h`):
  - Include guards using `#ifndef CLASSNAME_H` / `#define CLASSNAME_H` / `#endif`
  - Class declaration only
  - Minimal includes, prefer forward declarations where possible

- **Implementation Files** (`.cpp`):
  - Include corresponding header first
  - Method implementations in same order as header declaration

## Architecture and Design Principles

### Layered Architecture

The project follows a three-tier architecture:

1. **Presentation Layer**: CLI and user interaction
2. **Business Logic Layer**: Core task management functionality
3. **Data Layer**: Persistence and storage

Each layer should only depend on layers below it.

### Design Patterns

- **Repository Pattern**: Used in `TaskRepository` to abstract data access
- **Dependency Injection**: Pass dependencies via constructor (e.g., `TaskManager` receives `TaskRepository&`)
- **Single Responsibility Principle**: Each class has one clear purpose

### Error Handling

- Use exceptions for exceptional conditions
- Return `bool` for simple success/failure operations
- Validate inputs at the boundary (CLI layer)
- Display user-friendly error messages

### Performance Considerations

- This is a demo project - prioritize clarity over optimization
- Use `const&` for passing objects to avoid unnecessary copies
- Use move semantics where appropriate for C++17

## Language-Specific Best Practices

### C++17 Standards

- Use `std::filesystem` for file operations
- Prefer `auto` when type is obvious from context
- Use range-based for loops where appropriate
- Initialize variables at declaration

### Testing Requirements

All code contributions must include tests:

- **Unit Tests**: For individual classes and methods
- **Test Coverage**: Aim for core functionality coverage
- **Test Naming**: `TEST(ClassName, MethodName_Scenario)`
- **Assertions**: Use Google Test macros (`EXPECT_*`, `ASSERT_*`)

### Test-Driven Development (TDD)

When adding features:

1. Write the test first (it should fail)
2. Implement minimal code to make test pass
3. Run tests to verify
4. Refactor while keeping tests green

### Dependencies

- **nlohmann/json**: For JSON serialization (header-only)
- **Google Test**: For unit testing (fetched by CMake)
- Minimize external dependencies - prefer standard library

### Build System

- Use CMake for build configuration
- Support C++17 standard minimum
- Ensure cross-platform compatibility (Windows, Linux, macOS)

## Pull Request Guidelines

1. Ensure all tests pass (`ctest -C Debug`)
2. Follow coding standards outlined above
3. Update documentation if adding features
4. Keep commits focused and atomic
5. Write clear commit messages


