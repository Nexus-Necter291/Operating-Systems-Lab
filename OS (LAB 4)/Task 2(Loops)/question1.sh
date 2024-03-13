#!/bin/bash

# Loop through numbers from 1 to 10
for ((i = 1; i <= 10; i++)); do
    # Check if the number is even or odd
    if ((i % 2 == 0)); then
        echo "$i is even"
    else
        echo "$i is odd"
    fi
done
