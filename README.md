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

### Step 5: Build and Test the Application

Verify the CLI works end‑to‑end.

1. **Build the application**  
   Use your project build setup (e.g., CMake, Make, or VS Code task).
2. **Run the CLI**  
3. **Add some tasks**  
4. **List tasks**  
5. **Complete a task**  
  
### Step 6: Add a Document Agent
Establish a full workflow by adding a documentation-focused agent that finalizes and updates project docs after code implementation.

Workflow sequence:
1. Planning: Plan agent creates detailed plan
2. Implementation: TDD agent writes code + tests
3. Documentation: Document agent updates README + docs (added in this step)

Create the document agent:
1. File: Create `.github/agents/document.agent.md or add it from agents picker in the chat`
2. Role: Focus ONLY on documentation
3. Handoff: Configure it to receive from `tdd` (implementation) agent
4. Test: Run the workflow (Plan → Implement → Document) or invoke the document agent directly for a quick trial

#### Visual Guide
![Custom Agent Creation](img/custom%20agent.png)

### Step 7: Commit changes and create a PR:
Use your preferred way to commit changes and create a PR on GitHub.  

**Commit changes**
```bash
# Stage all changes
git add .

# Commit with a descriptive message
git commit -m "implement Task Manager CLI application"

# Push to your feature branch
git push origin feature/task-manager
```

**Create a pull request**

### Step 8 — Copilot as a Reviewer

**Where you work:** On **GitHub.com**, inside your open Pull Request.

**Checklist:**

* [ ] Navigate to your GitHub repository on GitHub.com
* [ ] Open the PR created 
* [ ] Assign Copilot as a reviewer to PR

#### Visual Guide
![Lab Instructions](img/review.png)

### Step 9 — Merge to PR to your fork's main branch. 

### Step 10 — Use the GitHub MCP Server

Leverage the GitHub MCP server to automate review and issue creation directly from VS Code.

Prerequisites:
1. Server shows as `Running` (see Step 1 setup).
2. MCP server is enabled in Copilot Chat tools picker.

Goal:
1. Generate a structured improvement report.
2. Automatically create issues for the highest‑priority items.

Workflow:
1. **Checkout the main branch**  
   ```bash
   git checkout main
   git pull origin main
   ``` 
2. Open Copilot Chat (Agent Mode).
3. (Optional) Select a planning or default agent; ensure MCP tools are active.
4. Send the Review Prompt below.
5. Inspect the response and optionally refine.
6. Send the Issue Creation Prompt to open GitHub issues.
7. Verify issues on GitHub.com.

Review Prompt (copy into chat):
```
Review the repository. List the top 5 improvement opportunities grouped by category:
Architecture, Code Quality, Testing, Documentation.
For each item provide:
- Short title
- One sentence justification
- Priority (High | Medium | Low)
- Suggested acceptance criteria (bullet list)
Return as a markdown table.
```

Issue Creation Prompt (after you agree with the list):
```
For the top 3 HIGH priority items, create GitHub issues. Each issue must include:
- Clear title
- Problem statement (why it matters)
- Proposed solution outline
- Acceptance criteria (bullet list)
- Labels: enhancement, prioritization/high
Respond with confirmation and the created issue numbers.
```

Verification:
1. Open GitHub in browser → Issues tab.
2. Confirm 3 new issues exist with correct labels and structured description.
3. Check acceptance criteria clarity; edit manually if further refinement needed.


### Step 11 — Assign Coding agent for a selected issue
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

#### Visual Guide
![Lab Instructions](img/coding%20agent.png)

### 2. Observe the automation

Watch as Copilot opens a branch and draft PR implementing the feature automatically. The Agent follows the patterns defined in your `AGENTS.md` file to ensure code consistency.

### That is it for today, well done!

### Labs Summary
The lab walked through a practical, agent‑assisted workflow to design, implement, document, and operationalize a C++ Task Manager CLI using GitHub Copilot and the GitHub MCP server.

Highlights:
- Context setup: Documentation (`PRODUCT.md`, `ARCHITECTURE.md`, `CONTRIBUTING.md`) and project‑wide custom instructions for consistent AI guidance.
- Planning: A dedicated `plan` agent generates an implementation plan aligned to architecture and coding standards, using `docs/plan-template.md` and prompt files.
- Implementation: The `tdd` agent autonomously creates code and tests following the plan and C++17 style guidelines.
- Documentation: A `document` agent finalizes README, product status, and usage notes.
- Git workflow: Commit and push changes on a feature branch; open a PR via GitHub CLI or web.
- Review & issues: Use the GitHub MCP server to produce a prioritized improvement report and automatically create issues for top items.
- Automation: Assign Copilot (Coding Agent) to an issue to open a branch and draft PR implementing the feature.

Key Practices:
- Start with clear, authoritative documentation; keep agents anchored to architecture and standards.
- Separate concerns via specialized agents (plan → implement → document) and explicit handoffs.
- Use templates and prompt files for consistent, high‑quality outputs.
- Iterate: refine instructions, prompts, and agent scopes based on observed behavior.
- Leverage MCP for repository automation (reviews, issues) and Copilot Coding Agent for hands‑on implementation.

