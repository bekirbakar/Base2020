#!/bin/bash

export FLASK_APP=app.py

curl -X POST -H "Content-Type: application/json" -d '{"text": "hello world hello"}' http://127.0.0.1:5000/unique-words
