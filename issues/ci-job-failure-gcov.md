### CI Job Failure: Unable to Locate Package gcov

#### Description
The CI job is failing due to an error indicating that the package 'gcov' cannot be located. This issue arises when attempting to install dependencies on Ubuntu-based runners since gcov is a bundled component of GCC, rather than a standalone package.

#### Recommendation
To resolve this issue, update all relevant steps in the `.github/workflows/ci.yml` file to install GCC instead of gcov directly. This will ensure that the necessary tools are available during the CI process.

#### References
- Workflow Commit: [1b9fbd7802c0e15f2cdb50d14e1a2a2bfff11c49](https://github.com/tjansen-philips/agentic-workflow-lab/commit/1b9fbd7802c0e15f2cdb50d14e1a2a2bfff11c49)
- Job Log: [Job Log](https://github.com/tjansen-philips/agentic-workflow-lab/actions/runs/19886642839/job/56995700841?pr=7)

#### Reported by: tjansen-philips
#### Date: 2025-12-03 08:09:24 (UTC)