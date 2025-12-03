### Issue Report

**Title:** CI 'Build and Test' job fails on Ubuntu due to incorrect package installation

**Description:**
The CI 'Build and Test' job fails on Ubuntu due to an incorrect package installation. The workflow currently attempts to install `gcov`, which leads to the following error:

`Unable to locate 'gcov'`. This should be replaced with `gcc` in the workflow.

Additionally, the job reports a missing build directory (`task-manager-cli/build`), possibly due to misreferenced or missing project structure.

**Proposed Solutions:**
1. Update the workflow to install `gcc` instead of `gcov`.
2. Ensure the `task-manager-cli` directory exists and all paths are correct in the workflow.

**Current Date:** 2025-12-03 08:15:24
**Reported by:** tjansen-philips