#!/bin/bash
#
# Script to sync with upstream repository
# This script helps keep your fork up-to-date with the upstream repository
#

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Configuration
UPSTREAM_URL="https://github.com/xebia/agentic-workflow-lab.git"

# Function to print colored output
print_info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Check if we're in a git repository
if ! git rev-parse --git-dir > /dev/null 2>&1; then
    print_error "Not in a git repository"
    exit 1
fi

# Check if upstream remote exists
if ! git remote get-url upstream > /dev/null 2>&1; then
    print_error "Upstream remote not configured"
    print_info "Run: git remote add upstream $UPSTREAM_URL"
    print_info "Then: git remote set-url --push upstream no-push"
    exit 1
fi

print_info "Upstream remote found"
git remote -v | grep upstream

# Check for uncommitted changes
if ! git diff-index --quiet HEAD --; then
    print_error "You have uncommitted changes. Please commit or stash them first."
    git status --short
    exit 1
fi

# Get current branch
CURRENT_BRANCH=$(git branch --show-current)
print_info "Current branch: $CURRENT_BRANCH"

# Fetch from upstream
print_info "Fetching from upstream..."
if git fetch upstream; then
    print_info "Successfully fetched from upstream"
else
    print_error "Failed to fetch from upstream"
    print_warning "This might be due to authentication issues or network problems"
    print_info "You can manually fetch using: git fetch upstream"
    exit 1
fi

# Ask user to confirm merge
echo ""
print_warning "Ready to merge upstream/main into $CURRENT_BRANCH"
read -p "Do you want to continue? (y/N): " -n 1 -r
echo ""

if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    print_info "Sync cancelled by user"
    exit 0
fi

# Merge upstream changes
print_info "Merging upstream/main into $CURRENT_BRANCH..."
if git merge upstream/main; then
    print_info "Successfully merged upstream changes"
else
    print_error "Merge failed - you may have conflicts to resolve"
    print_info "Resolve conflicts and then run: git commit"
    exit 1
fi

# Offer to push
echo ""
read -p "Do you want to push to origin/$CURRENT_BRANCH? (y/N): " -n 1 -r
echo ""

if [[ $REPLY =~ ^[Yy]$ ]]; then
    print_info "Pushing to origin/$CURRENT_BRANCH..."
    if git push origin "$CURRENT_BRANCH"; then
        print_info "Successfully pushed to origin"
    else
        print_error "Push failed"
        exit 1
    fi
fi

print_info "Sync complete!"
print_info "Your branch $CURRENT_BRANCH is now up-to-date with upstream"
