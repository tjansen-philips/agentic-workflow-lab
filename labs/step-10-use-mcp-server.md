# Step 10 — Use the GitHub MCP Server

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

---

## 🔍 **Optional: Explore More MCP Servers**

Extend your workflow with additional MCP servers:

- **[MCP Servers Directory](https://github.com/modelcontextprotocol/servers)** — Browse the full collection
- **[Azure DevOps MCP](https://github.com/microsoft/azure-devops-mcp)** — Manage work items, pipelines, and repos
- **[CodeScene MCP](https://github.com/codescene-oss/codescene-mcp-server)** — Code health and behavioral analysis
- **[10 Microsoft MCP Servers](https://developer.microsoft.com/blog/10-microsoft-mcp-servers-to-accelerate-your-development-workflow)** — Curated list to accelerate development
- **[Context7 MCP Server -- Up-to-date code documentation for LLMs and AI code editors](https://github.com/upstash/context7)**

---

Previous: [Step 9 — Merge PR to your fork's main branch](./step-09-merge-pr-main.md)  
Next: [Step 11 — Assign Coding agent for a selected issue](./step-11-assign-coding-agent.md)