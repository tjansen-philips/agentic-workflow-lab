# Context Engineering Lab - GitHub Copilot

Welcome to the Context Engineering Lab! This hands-on lab teaches you how to set up and use GitHub Copilot's context engineering features including custom instructions, custom agents, and prompt files to build a C++ application with AI assistance.

## 🎯 Lab Objectives

By completing this lab, you will learn how to:
- Set up project-wide context using custom instructions
- Create custom agents for planning and implementation
- Use prompt files to define reusable workflows
- Guide AI to generate high-quality, architecture-aligned code
- Leverage MCP servers for GitHub automation
- Utilize Copilot's coding agent for autonomous feature implementation

## Prerequisites

To complete the hands-on labs, ensure you have the following:

### Required Software
- **Visual Studio Code** (Latest) – [Download here](https://code.visualstudio.com/)
- **GitHub Copilot** - VS Code extension ([github.copilot](https://marketplace.visualstudio.com/items?itemName=GitHub.copilot) v1.284.0 or later)
- **GitHub Copilot Chat** - VS Code extension ([github.copilot-chat](https://marketplace.visualstudio.com/items?itemName=GitHub.copilot-chat) v0.25.1 or later)
- **GitHub Pull Requests** - VS Code extension ([github.vscode-pull-request-github](https://marketplace.visualstudio.com/items?itemName=GitHub.vscode-pull-request-github) 0.120.0 or later)
- **GitHub MCP Server** - VS Code extension for agentic workflows ([github.vscode-github-mcp](https://marketplace.visualstudio.com/items?itemName=github.vscode-github-mcp))
- **Git** – [Download here](https://git-scm.com/install/)

### Install the GitHub MCP server

1. Open the **Extensions** view

   * Press **Ctrl+Shift+X**.
   * In the search box, type **@mcp GitHub**.
   * Find **GitHub — Official GitHub MCP Server** and click **Install**.

2. Approve the authentication prompt

   * You will see a dialog, “The MCP Server Definition ‘github/github-mcp-server’ wants to authenticate to GitHub.”
   * Click **Allow**.

3. Pick your GitHub account

   * A quick pick appears asking which account to use.
   * Select your account, for example **YKhadas**.
   * VS Code will finish connecting the server.

4. Verify the server is running

   * Press **Ctrl+Shift+P** (Windows) or **Cmd+Shift+P** (Mac) to open the Command Palette.
   * Type **MCP: List Servers**, then press **Enter**.
   * In the list, confirm **github/github-mcp-server** shows **Running**.

5. Enable the server in Copilot Chat tools

   * Open the **GitHub Copilot Chat** panel.
   * Click the **Tools** icon at the bottom right of the chat window. It opens the **Configure Tools** picker.
   * In the list, find **MCP Server: github/github-mcp-server** and make sure it is **checked**.
   * Click **OK** to save.

You are set. If **github/github-mcp-server** does not show as Running, run **MCP: List Servers** again, or reload the window with **Developer: Reload Window**, then repeat step 5 to confirm the tool is checked.

### GitHub Repository Setup

1. **Fork this repository** to your GitHub account
2. **Clone your fork** locally:
   ```bash
   git clone https://github.com/YOUR-USERNAME/agentic-workflow-lab.git
   cd agentic-workflow-lab
   ```
3. **Create a feature branch** for your work:
   ```bash
   git checkout -b feature/task-manager
   git push -u origin feature/task-manager
   ```

> **Note:** All changes you make will go on this feature branch. You'll create a Pull Request later to merge your work.

## 🏗️ Application Overview

In this lab, you'll implement a **Task Manager CLI** - a command-line task management application for developers.

## 📚 Lab Structure

This repository contains a context engineering setup to guide AI interactions:

### 📄 Documentation Files
- **`docs/PRODUCT.md`** - Product vision, features, and goals
- **`docs/ARCHITECTURE.md`** - System design and architectural patterns
- **`docs/CONTRIBUTING.md`** - Code style, best practices, and guidelines

### ⚙️ Custom Instructions
- **`.github/copilot-instructions.md`** - Project-wide context automatically included in all AI interactions

### 🤖 Custom Agents
- **`.github/agents/plan.agent.md`** - Planning agent for creating detailed implementation plans
- **`.github/agents/tdd.agent.md`** - TDD implementation agent for writing code with tests

### 📋 Templates
- **`docs/plan-template.md`** - Structured template for implementation plans

### 💬 Prompt Files
- **`.github/prompts/plan-qna.prompt.md`** - Planning prompt with clarifying questions

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
  
### Step 2: Add Custom Instructions for Testing Guidelines

Enhance your project context by adding testing guidelines to custom instructions.

1. **Open VS Code Command Palette** (`Ctrl+Shift+P` or `Cmd+Shift+P`)
2. **Type and select**: `New instructions file`
3. **Add testing-specific guidelines** to complement the existing context

#### Visual Guide
![Lab Instructions](img/lab%20instructions.png)

> **Tip:** Custom instructions create persistent context that helps Copilot understand your project's conventions and standards.

### Step 3: Create an Implementation Plan

Use the planning agent to create a detailed, structured implementation plan.

1. **Open GitHub Copilot Chat** in VS Code (`Ctrl+Shift+I` or `Cmd+Shift+I`)

2. **Choose one of these approaches**:
   
   **Option A - Use the plan agent directly:**
   - Select `plan` from the agent picker in the chat interface
   - Type: `Create an implementation plan for the Task Manager CLI application as described in PRODUCT.md`
   
   **Option B - Use the prompt file:**
   - Type: `/plan-qna Add a Task Manager CLI application for managing tasks`

3. **Answer any clarifying questions** the agent asks about:
   - Feature priorities
   - Implementation details
   - Testing approach

4. **Review the generated plan**:
   - ✅ Follows the `plan-template.md` structure
   - ✅ Breaks down into clear, actionable tasks
   - ✅ Aligns with `ARCHITECTURE.md` design principles
   - ✅ Includes test considerations

### Step 4: Implement Using Agent Mode

Once the implementation plan is ready, use the TDD implementation agent to write the code.

1. Switch to the implementation agent:

In Copilot Chat, choose the TDD implementation agent configured in .github/agents/tdd.agent.md, or
Use the handoff link in the planning agent’s response (for example: “Start Implementation”).

2. **Let the agent work autonomously**:
   - The agent will create files, write code, and build the application
   - It will follow the architecture in ARCHITECTURE.md
   - It will adhere to code style in CONTRIBUTING.md
   - Watch as it implements each component

3. **Review the implementation**:
   - Check that files are created in the correct structure
   - Verify code follows the C++17 standard and style guide
   - Confirm tests are included (if TDD agent was used)

### Step 4: Build and Test the Application

1. **Build the application**:
 
2. **Add some tasks**:

3. **List tasks**:
   
4. **Complete a task**:
  
### Step 5: Add a Document Agent
Create a complete workflow, add a Document agent:

1. Plan agent creates detailed plan
2. TDD agent implements with tests
3. Document agent updates documentation - this agent you will add in this step

**To create the document agent:**

1. **Create a new file**: `.github/agents/document.agent.md`
2. **Define the agent's role**: Documentation and README updates
3. **Configure handoffs**: From TDD agent to document agent
4. **Test the agent**: Plan → Implement → Document. For the sake of time you can also can test the document agent using it directly. 

#### Visual Guide
![Custom Agent Creation](img/custom%20agent.png)

**Commit changes**

**Create PR**

## Exercise 8 — Copilot as a Reviewer

**Where you work:** On **GitHub.com**, inside your open Pull Request.

**Checklist:**

* [ ] Navigate to your GitHub repository on GitHub.com
* [ ] Open the PR created 
* [ ] Assign Copilot as a reviewer to PR

#### Visual Guide
![Lab Instructions](img/review.png)


## Exercise 9 — Use MCP server
Go back to VS Code IDE. 
Let's use Github MCP server. 

In Agent Mode, ask to review the application and provide list of improvements. 

Prompt: 

Next prompt: 
For the first top 3 improvements create an issue on github. 

The MCP server should create the issues. 
Go to github.com and valide that issues were created. 


## Exercise 10 — Assign Coding agent for a selected issue
**Where you work:** On **GitHub.com**, in the Issue UI.

**What and why:**
Copilot Agents can take an issue, create a branch, and open a draft PR with code changes. This exercise lets you hand off your feature request and observe Copilot’s automation.

**Checklist:**

* [ ] Open the issue you created in Exercise 9
* [ ] Assign it to **Copilot** (Coding Agent)
* [ ] Observe as Copilot opens a branch and draft PR implementing the feature

### 1. Assign the issue to Coding Agent
1. **Open your GitHub repository** in your browser and navigate to the **Issues** tab
2. **Click on the issue** you created in Exercise 9 (e.g., "Add Nutrition Info to Recipe Details")
3. **In the right-hand panel**, look for the **"Assignees"** section
4. **First, assign yourself** by clicking "Assign yourself" - this ensures you'll get notifications and maintain ownership
5. **Then, click the "Assign to Copilot" button** - this adds Copilot as a co-assignee to implement the feature
6. Both you and Copilot should now be listed as assignees

This will trigger the automated workflow where Copilot begins implementing your feature request while you maintain oversight and responsibility for the final outcome.


TODO: Agents file
#### Visual Guide
![Lab Instructions](img/coding%20agent.png)


### 2. Observe the automation

Watch as Copilot opens a branch and draft PR implementing the feature automatically. The Agent follows the patterns defined in your `AGENTS.md` file to ensure code consistency.

### That is it for today, well done!

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

