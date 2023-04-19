#!/bin/bash

cwd=$1

if [ -z "$cwd" ]; then
    echo "Provide working directory as first argument."
    exit 1
else
    cd $cwd
fi

python -m venv venv
source venv/bin/activate

pip install Flask
pip freeze >app/requirements.txt
