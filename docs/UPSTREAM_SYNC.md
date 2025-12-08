# Syncing with Upstream Repository

This document explains how to keep your fork synchronized with the upstream repository while ensuring your local changes remain separate.

## Overview

This repository (`tjansen-philips/agentic-workflow-lab`) is a fork of the upstream repository at `xebia/agentic-workflow-lab`. To stay current with upstream improvements while maintaining your custom changes, follow the process outlined below.

## Initial Setup

The upstream remote has already been configured with read-only access. You can verify this with:

```bash
git remote -v
```

You should see:
```
origin    https://github.com/tjansen-philips/agentic-workflow-lab (fetch)
origin    https://github.com/tjansen-philips/agentic-workflow-lab (push)
upstream  https://github.com/xebia/agentic-workflow-lab.git (fetch)
upstream  no-push (push)
```

## Syncing Process

### 1. Fetch Upstream Changes

First, fetch the latest changes from the upstream repository:

```bash
git fetch upstream
```

### 2. Checkout Your Main Branch

Switch to your main branch:

```bash
git checkout main
```

### 3. Merge Upstream Changes

Merge the upstream changes into your main branch:

```bash
git merge upstream/main
```

If there are conflicts, resolve them manually:
1. Open the conflicting files
2. Resolve the conflicts by choosing the appropriate changes
3. Stage the resolved files: `git add <file>`
4. Complete the merge: `git commit`

### 4. Push to Your Fork

Push the updated main branch to your fork:

```bash
git push origin main
```

### 5. Update Feature Branches

If you have feature branches that need the upstream changes:

```bash
git checkout <your-feature-branch>
git merge main
```

Or use rebase for a cleaner history:

```bash
git checkout <your-feature-branch>
git rebase main
```

## Safety Measures

### Push Protection

The upstream remote is configured with `no-push` to prevent accidentally pushing changes to the upstream repository. If you try to push to upstream, you'll see an error:

```bash
git push upstream main
# fatal: 'no-push' does not appear to be a git repository
```

This is intentional and prevents your changes from being sent to the upstream repository.

### Pull-Only Workflow

Your workflow should be:
- **Fetch** from upstream (read-only)
- **Merge** into your fork
- **Push** only to origin (your fork)

## Best Practices

1. **Regular Syncs**: Sync with upstream regularly (e.g., weekly) to minimize merge conflicts
2. **Clean State**: Before syncing, ensure your working directory is clean (`git status`)
3. **Feature Branches**: Keep your main branch clean and do all development work in feature branches
4. **Test After Sync**: After merging upstream changes, run tests to ensure compatibility
5. **Document Custom Changes**: Keep track of customizations you've made to avoid losing them during merges

## Troubleshooting

### Authentication Required

If you see authentication errors when fetching from upstream, ensure you have:
- A valid GitHub Personal Access Token (PAT)
- Proper permissions to access the upstream repository
- Git credential helper configured

### Merge Conflicts

If you encounter merge conflicts:
1. Don't panic - conflicts are normal when both upstream and your fork have changed the same files
2. Use `git status` to see which files have conflicts
3. Open each file and look for conflict markers (`<<<<<<<`, `=======`, `>>>>>>>`)
4. Decide which changes to keep (upstream, yours, or a combination)
5. Remove the conflict markers
6. Test your changes
7. Stage and commit the resolved files

### Diverged Histories

If your main branch has diverged significantly from upstream:
1. Consider creating a backup branch: `git branch backup-main`
2. Reset to upstream: `git reset --hard upstream/main`
3. Cherry-pick your custom commits: `git cherry-pick <commit-hash>`

## Summary

The upstream sync configuration ensures:
- ✅ You can fetch and merge changes from upstream
- ✅ You cannot accidentally push to upstream
- ✅ Your custom changes remain in your fork
- ✅ You stay up-to-date with upstream improvements
