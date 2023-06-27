#!/bin/bash

working_directory=$1

if [ -z "$working_directory" ]; then
    echo "Usage: clean-cache-files.sh <working-directory>"
    exit 1
fi

cd $working_directory

# Deletes intermediate and cache files from the current directory.

# File extensions to remove.
EXTENSIONS=(
    "*.aux"
    "*.bbl"
    "*.blg"
    "*.fdb_latexmk"
    "*.fls"
    "*.idx"
    "*.ilg"
    "*.ind"
    "*.lof"
    "*.log"
    "*.lot"
    "*.nav"
    "*.out"
    "*.snm"
    "*.synctex.gz"
    "*.toc"
    "*.xdv"
    "*.bcf"
    "*.cut"
    "*.run.xml"
)

# Remove files with specified extensions.
for ext in "${EXTENSIONS[@]}"; do
    find . -type f -name "$ext" -exec rm {} +
done

echo "Intermediate and cache files have been deleted."
