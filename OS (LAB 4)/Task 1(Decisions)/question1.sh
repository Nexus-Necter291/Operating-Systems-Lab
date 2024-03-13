#!/bin/bash

# Check if exactly 3 arguments are provided
if [ $# -ne 3 ]; then
    echo "Usage: $0 <number1> <number2> <number3>"
    exit 1
fi

# Assign command-line arguments to variables
num1=$1
num2=$2
num3=$3

# Function to find the maximum of three numbers
max_of_three() {
    if [ $1 -ge $2 ] && [ $1 -ge $3 ]; then
        echo $1
    elif [ $2 -ge $1 ] && [ $2 -ge $3 ]; then
        echo $2
    else
        echo $3
    fi
}

# Call the function with the provided numbers and print the result
result=$(max_of_three $num1 $num2 $num3)
echo "The largest number is: $result"
