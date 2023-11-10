#!/bin/bash

Input_DIR="./input"


gcc -o program main.c 

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    # Loop through all files in the input directory
    for file in $Input_DIR/*; do
        # Check if it is a regular file (not a directory or other type of file)
        if [ -f "$file" ]; then
            echo "Running with" $file
            ./program "$file"
        fi
    done
else
    echo "Compilation failedd"
fi
