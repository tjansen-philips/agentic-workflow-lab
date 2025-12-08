# Scripts

This directory contains utility scripts for managing the repository.

## setup-repository.sh

One-time setup script to configure upstream remote after cloning your fork.

### Usage

```bash
./scripts/setup-repository.sh
```

### What it does

1. Checks if you're in the correct repository directory
2. Adds the upstream remote pointing to `xebia/agentic-workflow-lab`
3. Configures push protection to prevent accidentally pushing to upstream
4. Displays the configured remotes

### When to use

Run this script once after cloning your fork of the repository.

## sync-upstream.sh

Automates the process of syncing your fork with the upstream repository.

### Usage

```bash
./scripts/sync-upstream.sh
```

### What it does

1. Verifies you're in a git repository
2. Checks that the upstream remote is configured
3. Checks for uncommitted changes (won't run if there are any)
4. Fetches latest changes from upstream
5. Prompts you to merge upstream/main into your current branch
6. Optionally pushes the updated branch to your fork

### Prerequisites

- Upstream remote must be configured (see [../docs/UPSTREAM_SYNC.md](../docs/UPSTREAM_SYNC.md))
- No uncommitted changes in your working directory
- Network access to the upstream repository
- Proper authentication credentials for fetching from upstream

### Example

```bash
$ ./scripts/sync-upstream.sh
[INFO] Upstream remote found
upstream	https://github.com/xebia/agentic-workflow-lab.git (fetch)
upstream	no-push (push)
[INFO] Current branch: main
[INFO] Fetching from upstream...
[INFO] Successfully fetched from upstream

[WARNING] Ready to merge upstream/main into main
Do you want to continue? (y/N): y

[INFO] Merging upstream/main into main...
[INFO] Successfully merged upstream changes

Do you want to push to origin/main? (y/N): y

[INFO] Pushing to origin/main...
[INFO] Successfully pushed to origin
[INFO] Sync complete!
[INFO] Your branch main is now up-to-date with upstream
```

## Making scripts executable

If a script is not executable, run:

```bash
chmod +x scripts/<script-name>.sh
```
