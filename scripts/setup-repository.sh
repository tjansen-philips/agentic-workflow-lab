#!/bin/bash
#
# Setup script for configuring the repository
# Run this script after cloning your fork
#

set -e

# Colors for output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Configuration
UPSTREAM_URL="https://github.com/xebia/agentic-workflow-lab.git"

echo -e "${GREEN}Setting up agentic-workflow-lab repository...${NC}\n"

# Check if we're in the right directory
if [ ! -f "README.md" ] || [ ! -d ".github" ]; then
    echo "Error: This script must be run from the root of the agentic-workflow-lab repository"
    exit 1
fi

# Check if upstream remote exists
if git remote get-url upstream > /dev/null 2>&1; then
    echo -e "${YELLOW}Upstream remote already configured:${NC}"
    git remote -v | grep upstream
    echo ""
    read -p "Do you want to reconfigure it? (y/N): " -n 1 -r
    echo ""
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        git remote remove upstream
        echo "Removed existing upstream remote"
    else
        echo "Keeping existing upstream configuration"
        exit 0
    fi
fi

# Add upstream remote
echo "Adding upstream remote..."
git remote add upstream "$UPSTREAM_URL"

# Configure push protection
echo "Configuring push protection for upstream..."
git remote set-url --push upstream no-push

# Verify configuration
echo -e "\n${GREEN}✓ Setup complete!${NC}\n"
echo "Configured remotes:"
git remote -v

echo -e "\n${GREEN}Next steps:${NC}"
echo "1. Fetch from upstream: git fetch upstream"
echo "2. Sync your fork: ./scripts/sync-upstream.sh"
echo "3. See docs/UPSTREAM_SYNC.md for more information"
