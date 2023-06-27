#!/bin/bash

directory=${1:-.}

declare -A arr

while IFS= read -r -d '' file; do
    checksum=$(md5sum "$file" | awk '{ print $1 }')

    if [[ ${arr[$checksum]} ]]; then
        echo "  $file"
        echo "  ${arr[$checksum]}"
        echo
    fi

    arr[$checksum]="$file"
done < <(find "$directory" -type f -print0)
