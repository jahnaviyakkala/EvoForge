#!/bin/bash

# Ensure Python is installed
python3 --version > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "Python 3 is not installed. Please install it first."
    exit 1
fi

# Run the application
python3 main.py
