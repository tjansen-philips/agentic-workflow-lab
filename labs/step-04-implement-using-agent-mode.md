# Step 4: Implement Using Agent Mode

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

---

Previous: [Step 3 — Create an Implementation Plan](./step-03-create-implementation-plan.md)  
Next: [Step 5 — Build and Test the Application](./step-05-build-and-test.md)