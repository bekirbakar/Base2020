#/bin/bash

# This script takes an input string, converts it to lowercase, removes non-alphabetic characters, and replaces spaces
# with hyphens.

input_data=$1

echo ${input_data} | tr 'A-Z' 'a-z' | tr -c 'a-zA-Z\n' ' ' | tr -s ' ' | tr ' ' '-'
