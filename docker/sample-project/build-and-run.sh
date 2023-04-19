#!/bin/bash

# Set your project name here.
PROJECT_NAME="example-project"

# Build the Docker image.
docker build -t $PROJECT_NAME .

# Run the Docker container, mapping the container's port 5000 to the host's
# port 8080.
docker run -p 8080:5000 --name $PROJECT_NAME-container --rm $PROJECT_NAME
