# Step 6: Add a Document Agent

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
5. Inspiration: [your first documentation agent](https://docs.github.com/en/copilot/tutorials/customization-library/custom-agents/your-first-custom-agent)

#### Visual Guide
![Custom Agent Creation](../img/custom%20agent.png)

---

Previous: [Step 5 — Build and Test the Application](./step-05-build-and-test.md)  
Next: [Step 7 — Commit changes and create a PR](./step-07-commit-and-pr.md)