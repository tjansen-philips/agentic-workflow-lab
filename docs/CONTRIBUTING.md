# Contributing Guidelines

## Development Environment

### Prerequisites
- C++ compiler with C++17 support (g++ 7+ or clang++ 5+)
- GNU Make
- Git for version control

### Setup
```bash
git clone <repository-url>
cd agentic-workflow-lab
make
```

## Code Style and Standards

### C++ Style Guidelines

- **Standard**: Use C++17 features and standard library
- **Naming Conventions**:
  - Classes: `PascalCase` (e.g., `TaskManager`, `FileStorage`)
  - Functions/Methods: `camelCase` (e.g., `addTask`, `saveTasks`)
  - Variables: `camelCase` (e.g., `taskId`, `description`)
  - Constants: `UPPER_SNAKE_CASE` (e.g., `MAX_TASKS`)
  - Private members: prefix with `m_` (e.g., `m_tasks`)

- **Formatting**:
  - Indent with 4 spaces (no tabs)
  - Opening brace on same line for functions and classes
  - Use spaces around operators
  - One statement per line

- **Header Files**:
  - Use include guards: `#ifndef FILENAME_H` / `#define FILENAME_H`
  - Separate declaration from implementation (.h and .cpp files)
  - Include only what you use

### Example Code Style

```cpp
class TaskManager {
public:
    TaskManager();
    bool addTask(const std::string& description, Priority priority);
    std::vector<Task> listTasks() const;
    
private:
    std::vector<Task> m_tasks;
    int m_nextId;
};
```

## Best Practices

### General Principles
1. **Keep it simple**: Favor clarity over cleverness
2. **Single Responsibility**: Each class/function should do one thing well
3. **DRY (Don't Repeat Yourself)**: Extract common code into functions
4. **RAII**: Use Resource Acquisition Is Initialization for resource management
5. **Error Handling**: Check return values and handle errors gracefully

### Memory Management
- Prefer stack allocation over heap allocation when possible
- Use smart pointers (`std::unique_ptr`, `std::shared_ptr`) if heap allocation is needed
- Avoid raw `new` and `delete`
- Use standard containers (`std::vector`, `std::string`) for automatic memory management

### File I/O
- Always check if file operations succeed
- Close files properly (use RAII with `std::fstream`)
- Use `std::getline` for reading lines
- Handle missing files gracefully

### Error Handling
- Use return codes (bool, int) for success/failure indication
- Return error codes rather than exceptions for expected failures
- Log errors with descriptive messages
- Never silently fail

## Building and Testing

### Build Commands
```bash
# Build the project
make

# Clean build artifacts
make clean

# Run tests
make test
```

### Before Committing
1. Build successfully with no warnings: `make clean && make`
2. Run all tests and ensure they pass: `make test`
3. Test manually with various inputs
4. Review your changes: `git diff`

## Git Workflow

### Commit Messages
- Use clear, descriptive commit messages
- Start with a verb in present tense (e.g., "Add", "Fix", "Update")
- Keep first line under 50 characters
- Add detailed description if needed

Example:
```
Add file storage for task persistence

- Implement FileStorage class with save/load methods
- Use pipe-delimited text format for simplicity
- Handle file errors gracefully with clear messages
```

### Branch Strategy
- Work on feature branches
- Name branches descriptively: `feature/task-persistence`, `fix/file-handling`
- Keep commits focused and atomic

## Testing Guidelines

### Unit Test Practices
- Test one thing per test case
- Use descriptive test names
- Test both success and failure cases
- Test edge cases (empty lists, invalid IDs, file errors)

### Manual Testing Checklist
- [ ] Add tasks with different priorities
- [ ] List tasks shows correct information
- [ ] Complete task marks it correctly
- [ ] Delete task removes it
- [ ] Tasks persist after restart
- [ ] Invalid commands show helpful errors
- [ ] File is created if it doesn't exist

## Code Review Guidelines

### As a Reviewer
- Check for code style consistency
- Verify error handling is present
- Look for potential memory leaks
- Ensure tests are included
- Validate that changes match requirements

### As an Author
- Self-review your changes before submitting
- Write clear PR description
- Respond to feedback constructively
- Keep changes focused and minimal

## Common Pitfalls to Avoid

1. **Memory Leaks**: Always clean up resources
2. **Unchecked Errors**: Always validate file operations and user inputs
3. **Magic Numbers**: Use named constants instead
4. **God Classes**: Keep classes focused on single responsibility
5. **Poor Error Messages**: Provide context in error messages
6. **Ignoring Warnings**: Fix all compiler warnings

## Questions?

If you have questions or need clarification on any of these guidelines, please open an issue or reach out to the maintainers.
