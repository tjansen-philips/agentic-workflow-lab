# Task Manager CLI - Architecture and Design

## System Overview

The Task Manager CLI is a single-executable command-line application with a layered architecture that separates concerns between presentation, business logic, and data persistence. We are buiding applictaion for demo, do not overcomplicate it. 

## Design Patterns

### Layered Architecture
- Clear separation between presentation, business logic, and data
- Each layer depends only on the layer below it
- Easy to test and modify independently

### Repository Pattern 
- Abstract data persistence details
- Easy to swap storage implementations later

## Security Considerations
- No authentication required (single-user, local)

## Tests
- add unit tests