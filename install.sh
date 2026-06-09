#!/bin/bash

set -e

echo "Update"
sudo apt update

echo "Compile Tools"
sudo apt install -y \
    build-essential \
    cmake \
    git

echo "OpenGL"
sudo apt install -y \
    mesa-utils \
    libgl1-mesa-dev

echo "GLFW && X11"
sudo apt install -y \
    libglfw3-dev \
    libx11-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev \
    libxxf86vm-dev
