#!/bin/bash

# Set the log file path.
LOG_FILE="cleanup-mac.log"

# Redirect all output to the log file.
exec > >(tee -i "$LOG_FILE")
exec 2>&1

# Change to home directory.
cd ~

set -e

# Clean up outdated versions of installed packages.
brew cleanup
brew upgrade

# Clean up Homebrew's cache.
brew cleanup --prune-prefix

# Clean up orphaned packages.
brew cleanup -s

# Clean up large files and folders.
du -a -h | sort -rh | grep -v -E '^du: \./(Library|System|Users|private|Volumes)' | head -20
