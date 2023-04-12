#!/bin/bash

# This script removes intermediate and cache files generated during LaTeX
# document compilation. It is useful for cleaning up a working directory
# containing LaTeX source files.

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
