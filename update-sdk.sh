#!/bin/bash

# update-sdk.sh - Update the brain-sdk submodule to the latest version from GitHub
# Usage: ./update-sdk.sh [--push]
#   --push: Automatically commit and push the update

set -e

PUSH=false
if [[ "$1" == "--push" ]]; then
  PUSH=true
fi

echo "Updating brain-sdk submodule..."
echo ""

cd brain-sdk
git fetch origin
git checkout main
git pull origin main
cd ..

echo ""
echo "✓ brain-sdk updated to latest version"
echo ""

if [ "$PUSH" = true ]; then
  echo "Committing and pushing update..."
  git add brain-sdk
  git commit -m "Updated brain-sdk"
  git push
  echo ""
  echo "✓ Changes committed and pushed"
else
  echo "Don't forget to commit the update:"
  echo "  git add brain-sdk"
  echo "  git commit -m \"Updated brain-sdk\""
  echo "  git push"
  echo ""
  echo "Or run: ./update-sdk.sh --push"
fi
