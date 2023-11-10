#!/bin/bash

Input_DIR="./input"

# Compile the C program
gcc -o program main.c 


if [ $? -eq 0 ]; then
    # Loop through all files in the input directory
    for file in $Input_DIR/*; do
         if [ -f "$file" ]; then
            echo "Running with" "$file"
            ./program "$file"
    done
else
    echo "Compilation failed"
fi
