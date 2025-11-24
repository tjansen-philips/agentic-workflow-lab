# Contributing Guidelines

## Development Environment

### Prerequisites
- C++ compiler with C++17 support (g++ 7+ or clang++ 5+)
- GNU Make
- Git for version control

## Code Style and Standards

### C++ Style Guidelines

**Naming Conventions**:
- Classes: `PascalCase` (e.g., `TaskManager`)
- Functions/Methods: `camelCase` (e.g., `addTask`)
- Variables: `camelCase` (e.g., `taskId`)
- Constants: `UPPER_SNAKE_CASE` (e.g., `MAX_TASKS`)
- Private members: prefix with `m_` (e.g., `m_tasks`)

**Formatting**:
- Indent with 4 spaces (no tabs)
- Opening brace on same line
- One statement per line

## C++ Best Practices

### Memory & Resources
- Prefer stack allocation over heap when possible
- Use smart pointers (`std::unique_ptr`, `std::shared_ptr`) instead of raw `new`/`delete`
- Use RAII for resource management (files, memory, locks)
- Pass large objects by const reference to avoid copies

### Modern C++17 Features
- Use `auto` for complex types and iterators
- Range-based for loops: `for (const auto& item : items)`
- Use `nullptr` instead of `NULL`
- Use `constexpr` for compile-time constants
- Leverage `std::optional` for optional values
- Use `enum class` for type-safe enums

### Safety & Correctness
- Initialize all variables at declaration
- Mark methods `const` when they don't modify state
- Avoid C-style casts; use `static_cast`, `const_cast`
- Check return values from file operations and system calls
- Handle errors gracefully with clear messages

### Code Organization
- Use include guards in headers
- Keep functions short and focused (< 30 lines ideally)
- Separate interface (.h) from implementation (.cpp)
- Include only what you use

## Building and Testing

```bash
# Build the project
make

# Clean build artifacts
make clean

# Run tests
make test
```
