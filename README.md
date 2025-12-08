# Agentic workflow Lab - GitHub Copilot

## 🎯 Lab Objectives

By completing this lab, you will learn how to:
- Set up project-wide context using custom instructions
- Create custom agents for planning and implementation
- Use prompt files to define reusable workflows
- Guide AI to generate high-quality, architecture-aligned code
- Leverage MCP servers for GitHub automation
- Utilize Copilot's coding agent for autonomous feature implementation and review

## Prerequisites

To complete the hands-on labs, ensure you have the following:

### Required Software
- **Visual Studio Code** (Latest) – [Download here](https://code.visualstudio.com/)
- **GitHub Copilot** - VS Code extension ([github.copilot](https://marketplace.visualstudio.com/items?itemName=GitHub.copilot) v1.284.0 or later)
- **GitHub Copilot Chat** - VS Code extension ([github.copilot-chat](https://marketplace.visualstudio.com/items?itemName=GitHub.copilot-chat) v0.25.1 or later)
- **GitHub Pull Requests**(optional) - VS Code extension ([github.vscode-pull-request-github](https://marketplace.visualstudio.com/items?itemName=GitHub.vscode-pull-request-github) 0.120.0 or later)
- **GitHub MCP Server** - VS Code extension for agentic workflows ([github.vscode-github-mcp](https://github.com/github/github-mcp-server))
- **Git** – [Download here](https://git-scm.com/install/)

### Install the GitHub MCP server

You have several options:

1. You can install the server from the official page: https://github.com/github/github-mcp-server

2. Or you can install the sevrer from the extensions:
   - Open the **Extensions** view
   - Press **Ctrl+Shift+X**.
   - In the search box, type **@mcp GitHub**.
   - Find **GitHub — Official GitHub MCP Server** and click **Install**.

3. Approve the authentication prompt
   - You will see a dialog, "The MCP Server Definition 'github/github-mcp-server' wants to authenticate to GitHub."
   - Click **Allow**.

4. Pick your GitHub account
   - A quick pick appears asking which account to use.
   - Select your account, for example **YKhadas**.
   - VS Code will finish connecting the server.

5. Verify the server is running
   - Press **Ctrl+Shift+P** (Windows) or **Cmd+Shift+P** (Mac) to open the Command Palette.
   - Type **MCP: List Servers**, then press **Enter**.
   - In the list, confirm **github/github-mcp-server** shows **Running**.

6. Enable the server in Copilot Chat tools
   - Open the **GitHub Copilot Chat** panel.
   - Click the **Tools** icon at the bottom right of the chat window. It opens the **Configure Tools** picker.
   - In the list, find **MCP Server: github/github-mcp-server** and make sure it is **checked**.
   - Click **OK** to save.

You are set. If **github/github-mcp-server** does not show as Running, run **MCP: List Servers** again, or reload the window with **Developer: Reload Window**, then repeat step 6 to confirm the tool is checked.

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

In this lab, you'll implement a simple **Task Manager CLI** - a command-line task management application.


## 🚀 Labs Navigation

The full lab steps are now organized under `labs/` for convenient navigation:

- [Step 1 — Explore the Context Engineering Setup](labs/step-01-explore-context.md)
- [Step 2 — Add Custom Instructions for Testing Guidelines](labs/step-02-add-custom-instructions.md)
- [Step 3 — Create an Implementation Plan](labs/step-03-create-implementation-plan.md)
- [Step 4 — Implement Using Agent Mode](labs/step-04-implement-using-agent-mode.md)
- [Step 5 — Build and Test the Application](labs/step-05-build-and-test.md)
- [Step 6 — Add a Document Agent](labs/step-06-add-document-agent.md)
- [Step 7 — Commit changes and create a PR](labs/step-07-commit-and-pr.md)
- [Step 8 — Copilot as a Reviewer](labs/step-08-copilot-reviewer.md)
- [Step 9 — Merge PR to your fork's main branch](labs/step-09-merge-pr-main.md)
- [Step 10 — Use the GitHub MCP Server](labs/step-10-use-mcp-server.md)
- [Step 11 — Assign Coding agent for a selected issue](labs/step-11-assign-coding-agent.md)

