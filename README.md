# Context Engineering Lab - GitHub Copilot

Welcome to the Context Engineering Lab! This hands-on lab teaches you how to set up and use GitHub Copilot's context engineering features including custom instructions, custom agents, and prompt files to build a C++ application with AI assistance.

## 🎯 Lab Objectives

By completing this lab, you will learn how to:
- Set up project-wide context using custom instructions
- Create custom agents for planning and implementation
- Use prompt files to define reusable workflows
- Guide AI to generate high-quality, architecture-aligned code
- Implement a complete C++ CLI application using agent mode

## 📋 Prerequisites

- Visual Studio Code with GitHub Copilot enabled
- C++ compiler (g++ 7+ or clang++ 5+) with C++17 support
- GNU Make
- Git
- Basic familiarity with C++ and command-line tools

## 🏗️ Application Overview

In this lab, you'll implement a **Task Manager CLI** - a command-line task management application for developers. The application features:

- ✅ Add tasks with descriptions and priorities (low, medium, high)
- 📝 List all tasks with their status
- ✔️ Mark tasks as complete
- 🗑️ Delete tasks
- 💾 Save/load tasks from a file

This application demonstrates context engineering because it has:
- Clear requirements and scope
- Multiple components (CLI, business logic, data persistence)
- Testable functionality
- Architectural patterns to follow
- Small enough to implement quickly with AI assistance

## 📚 Lab Structure

This repository contains the context engineering setup:

### Documentation Files
- **PRODUCT.md** - Product vision, features, and goals
- **ARCHITECTURE.md** - System design and architectural patterns
- **CONTRIBUTING.md** - Code style, best practices, and guidelines

### Custom Instructions
- **.github/copilot-instructions.md** - Project-wide context automatically included in all AI interactions

### Custom Agents
- **.github/agents/plan.agent.md** - Planning agent for creating implementation plans
- **.github/agents/tdd.agent.md** - TDD implementation agent for writing code

### Templates
- **plan-template.md** - Template structure for implementation plans

### Prompt Files
- **.github/prompts/plan-qna.prompt.md** - Planning prompt with clarifying questions

## 🚀 Lab Steps

### Step 1: Explore the Context Engineering Setup

1. **Review the documentation files** to understand the project:
   - Open `PRODUCT.md` and read about the Task Manager's features and goals
   - Open `ARCHITECTURE.md` to understand the layered architecture design
   - Open `CONTRIBUTING.md` to learn the C++ coding standards

2. **Examine the custom instructions**:
   - Open `.github/copilot-instructions.md`
   - Notice how it references the documentation files
   - These instructions are automatically included in all Copilot interactions

3. **Review the custom agents**:
   - Open `.github/agents/plan.agent.md` - specialized for planning
   - Open `.github/agents/tdd.agent.md` - specialized for TDD implementation
   - Notice the handoff configuration from planning to implementation

4. **Check the templates and prompts**:
   - Open `plan-template.md` to see the implementation plan structure
   - Open `.github/prompts/plan-qna.prompt.md` for the clarifying questions prompt

### Step 2: Create an Implementation Plan

Now you'll use the planning agent to create a detailed implementation plan.

1. **Open GitHub Copilot Chat** in VS Code (Ctrl+Alt+I or Cmd+Alt+I)

2. **Select the `plan` agent** from the agent picker in the chat interface

3. **Alternatively, use the prompt file** by typing:
   ```
   /plan-qna Add a Task Manager CLI application for managing tasks
   ```

4. **Or directly ask the plan agent**:
   ```
   @plan Create an implementation plan for the Task Manager CLI application as described in PRODUCT.md
   ```

5. **Answer any clarifying questions** the agent asks

6. **Review the generated plan**:
   - Does it follow the plan-template.md structure?
   - Does it break down into clear, actionable tasks?
   - Does it align with ARCHITECTURE.md design?
   - Are all components covered (CLI, TaskManager, FileStorage, Task)?

7. **Iterate if needed**:
   - Ask follow-up questions
   - Request refinements to the plan
   - Ensure all requirements are covered

8. **Save the plan** (optional):
   - Ask the agent to save the plan to a file: "Save this plan to task-manager-plan.md"
   - Or copy it to a new file manually

### Step 3: Implement Using Agent Mode

Now you'll implement the application using GitHub Copilot's agent mode.

1. **Switch to Agent Mode** in GitHub Copilot Chat (look for the agent icon or use the handoff from the plan agent)

2. **Provide the implementation plan**:
   ```
   Implement the Task Manager CLI according to the plan we just created. Follow TDD principles.
   ```

   Or if you saved the plan to a file:
   ```
   Implement #task-manager-plan.md following TDD principles
   ```

3. **Let the agent work autonomously**:
   - The agent will create files, write code, and build the application
   - It will follow the architecture in ARCHITECTURE.md
   - It will adhere to code style in CONTRIBUTING.md
   - Watch as it implements each component

4. **Review the implementation**:
   - Check that files are created in the correct structure
   - Verify code follows the C++17 standard and style guide
   - Ensure error handling is implemented
   - Confirm tests are included (if TDD agent was used)

### Step 4: Build and Test the Application

1. **Build the application**:
   ```bash
   make clean && make
   ```

2. **Test the help command**:
   ```bash
   ./task-manager help
   ```

3. **Add some tasks**:
   ```bash
   ./task-manager add "Implement file storage" high
   ./task-manager add "Add unit tests" medium
   ./task-manager add "Update documentation" low
   ```

4. **List tasks**:
   ```bash
   ./task-manager list
   ```

5. **Complete a task**:
   ```bash
   ./task-manager complete 1
   ./task-manager list
   ```

6. **Delete a task**:
   ```bash
   ./task-manager delete 2
   ./task-manager list
   ```

7. **Verify persistence**:
   - Exit and run `./task-manager list` again
   - Tasks should be loaded from the saved file

### Step 5: Iterate and Refine

1. **Review the code quality**:
   - Does it match ARCHITECTURE.md design?
   - Does it follow CONTRIBUTING.md style?
   - Are error cases handled?

2. **Ask for improvements** if needed:
   ```
   Review the code against ARCHITECTURE.md and suggest improvements
   ```

3. **Add features** (optional exercises):
   - Add task filtering by priority
   - Add task search functionality
   - Add task editing capability
   - Add better formatted output with colors

### Step 6: Experiment with Context Engineering

Try these experiments to see how context engineering improves AI assistance:

**Experiment A: Without Context**
1. Open a new chat without referencing the docs
2. Ask: "Add a feature to sort tasks by priority"
3. Observe the response quality

**Experiment B: With Context**
1. Open a new chat
2. Ask: "Add a feature to sort tasks by priority, following the architecture in ARCHITECTURE.md and code style in CONTRIBUTING.md"
3. Compare the response quality

**Experiment C: Update Documentation**
1. Modify ARCHITECTURE.md to add a new design requirement
2. Ask the agent to implement a feature
3. Verify it follows the updated architecture

## 🎓 Key Takeaways

### Context Engineering Benefits
- ✅ **Consistency**: AI follows your architectural patterns and style
- ✅ **Quality**: Better code generation aligned with project standards
- ✅ **Efficiency**: Less back-and-forth to correct misunderstandings
- ✅ **Persistence**: Context maintained across chat sessions
- ✅ **Scalability**: Team members get consistent AI assistance

### Best Practices Learned
1. **Start with clear documentation** - Product, Architecture, Contributing
2. **Use custom instructions** - Automatic context for all interactions
3. **Create specialized agents** - Separate planning from implementation
4. **Define templates** - Ensure consistent output structure
5. **Iterate and refine** - Update context based on observed AI behavior

### Custom Agents vs Tools
- **Custom agents** have specialized personas and workflows
- **Handoffs** create guided transitions between agents
- **Prompt files** add variants to the same workflow
- **Instructions** provide persistent, project-wide context

## 🔬 Advanced Exercises

### Exercise 1: Add a New Agent
Create a review agent (`.github/agents/review.agent.md`) that:
- Reviews code against architecture and style guides
- Identifies potential bugs or improvements
- Suggests refactoring opportunities

### Exercise 2: Enhance the Template
Modify `plan-template.md` to include:
- Security considerations section
- Performance requirements
- Accessibility guidelines

### Exercise 3: Create Domain-Specific Prompts
Add prompt files for common tasks:
- `.github/prompts/feature.prompt.md` - Add a new feature
- `.github/prompts/bugfix.prompt.md` - Fix a bug
- `.github/prompts/refactor.prompt.md` - Refactor code

### Exercise 4: Multi-Agent Workflow
Create a complete workflow:
1. Plan agent creates detailed plan
2. TDD agent implements with tests
3. Review agent reviews the code
4. Document agent updates documentation

### Exercise 5: Context Hierarchy
Experiment with different context levels:
- Global instructions (`.github/copilot-instructions.md`)
- Module-specific instructions (create per-directory)
- Feature-specific context (in implementation plans)

## 📖 Additional Resources

### GitHub Copilot Documentation
- [Custom Instructions](https://code.visualstudio.com/docs/copilot/copilot-customization)
- [Custom Agents](https://code.visualstudio.com/docs/copilot/copilot-agents)
- [Prompt Files](https://code.visualstudio.com/docs/copilot/prompt-files)

### Context Engineering Articles
- [Context Engineering Best Practices](https://github.blog/2023-11-08-ai-powered-development-best-practices/)
- [Prompt Engineering Guide](https://www.promptingguide.ai/)

### C++ Resources
- [C++17 Features](https://en.cppreference.com/w/cpp/17)
- [Modern C++ Best Practices](https://isocpp.github.io/CppCoreGuidelines/)

## 🤝 Contributing

This lab is designed to be a learning resource. If you have suggestions for improvements:
1. Try the lab and take notes on your experience
2. Identify areas that could be clearer or more helpful
3. Submit issues or pull requests with your suggestions

## 📝 License

This lab is provided as-is for educational purposes.

## ✨ What's Next?

After completing this lab, you can:
- Apply context engineering to your own projects
- Create custom agents for your team's workflows
- Share your context engineering setup across projects
- Teach others about effective AI-assisted development

---

**Happy Learning! 🚀**

Remember: Context engineering is about empowering AI to understand your project deeply. The better your context, the better your AI assistance!
