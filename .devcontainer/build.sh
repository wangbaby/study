#!/bin/bash

export HOST_USER_ID="$(id -u)"
export HOST_GROUP_ID="$(id -g)"
export HOST_USER_NAME="$(id -un)"
export HOST_GROUP_NAME="$(id -gn)"

# --build
docker-compose up -d "$*"