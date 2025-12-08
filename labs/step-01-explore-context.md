# Step 1 — Explore the Context Engineering Setup

This step introduces the structure of the repository and shows how context is organized to support consistent, high-quality AI interactions.

---

## 🧭 **1. Explore the Project Documentation**

Start by reviewing the core documents that define the product, architecture, and development standards:

### **📄 Documentation Files**
- **`docs/PRODUCT.md`**  
  Describes the product vision, feature set, and overall goals of the Task Manager.

- **`docs/ARCHITECTURE.md`**  
  Outlines the system design, layered architecture, and key architectural patterns.

- **`docs/CONTRIBUTING.md`**  
  Provides coding standards and best practices for contributing to the codebase.

These files establish the shared understanding required for both developers and AI agents.

---

## ⚙️ **2. Review and update the Custom Copilot Instructions**

### Helpful links for customizing responses

- **Repository Custom Instructions:** Configure project-wide instructions in VS Code — [add-repository-instructions](https://docs.github.com/en/copilot/how-tos/configure-custom-instructions/add-repository-instructions?tool=vscode)
- **Custom Agents Concept:** Build tailored Copilot agents - [custom-agents](https://code.visualstudio.com/docs/copilot/customization/custom-agents)
- **Customization Library:** Examples of well-defined instructions, prompts, and agents - [customization-library](https://docs.github.com/copilot/tutorials/customization-library)
- **Community Examples:** Curated list of prompts, agents, and repos - [awesome-copilot](https://github.com/github/awesome-copilot)
- **VS Code open sourced:** Instructions used to buid VS code - [microsoft/vscode](https://github.com/microsoft/vscode/tree/main/.github)


- Open **`.github/copilot-instructions.md`**  
  This file defines the project-wide context injected into all GitHub Copilot interactions.

Pay attention to:
- How the file references your documentation (PRODUCT, ARCHITECTURE, CONTRIBUTING)  
- Update CONTRIBUTING guidlines for the language of your choice. 
- Adjust PRODUCT, ARCHITECTURE, custom-instructions file if needed.

This is the backbone of the context engineering setup.

---

## 🤖 **3. Examine the Custom Agents**

The repository includes specialized agents for planning and TDD workflows:

- **`.github/agents/plan.agent.md`**  
  A planning-focused agent that produces detailed implementation plans.

- **`.github/agents/tdd.agent.md`**  
  A TDD-focused agent that writes tests and implementation code.

These agents hand off work between each other, forming a structured development pipeline.

---

## 📝 **4. Check the Templates and Prompts**

These files support the agent workflows:

- **`docs/plan-template.md`**  
  A structured template for building consistent implementation plans.

- **`.github/prompts/plan-qna.prompt.md`**  
  Clarifying questions used during the planning phase to ensure completeness and alignment.

---

## ✅ **What You Should Do in This Step**

1. Open each documentation file and skim key concepts  
2. Understand how `.github/copilot-instructions.md` connects the repository context  
3. Review both custom agents and their roles  
4. Familiarize yourself with the plan template and the clarifying-questions prompt  

---

👉 **Next Step:**  
[Step 2 — Add Custom Instructions for Testing Guidelines](./step-02-add-custom-instructions.md)
