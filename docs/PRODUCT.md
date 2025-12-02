# Task Manager CLI - Quick Demo Version

## Product Overview

A minimal task manager CLI for quick demos. 

## Core Features (MVP)

### Must-Have Features
1. **Add Task**: Create a task with just a description
   ```
   add "Buy groceries"
   ```

2. **List Tasks**: Show all tasks with simple numbering
   ```
   list
   ```

3. **Complete Task**: Mark a task as done by number
   ```
   complete 1
   ```

4. **Clear Tasks**: Remove all tasks and reset ID counter
   ```
   clear
   ```

## Implementation Guidelines

### Keep It Simple
- File persistence implemented using JSON (in executable directory)

