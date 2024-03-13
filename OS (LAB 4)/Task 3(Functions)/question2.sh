#!/bin/bash

# Function to calculate factorial recursively
factorial() {
    local num=$1

    # Base case: factorial of 0 or 1 is 1
    if [ $num -eq 0 ] || [ $num -eq 1 ]; then
        echo 1
    else
        # Recursive case: factorial(n) = n * factorial(n-1)
        local sub_result=$(factorial $((num - 1)))
        echo $((num * sub_result))
    fi
}

# Main script
echo "Enter a number to calculate its factorial:"
read number

# Check if the input is a positive integer
if ! [[ $number =~ ^[0-9]+$ ]]; then
    echo "Error: Please enter a positive integer."
    exit 1
fi

result=$(factorial $number)
echo "Factorial of $number is: $result"
