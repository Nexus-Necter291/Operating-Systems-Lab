#!/bin/bash
calculate_sum_of_digits() {
    local number=$1
    local sum=0
    while [ $number -gt 0 ]; do
        # Extract the last digit
        digit=$((number % 10))
        # Add the digit to the sum
        sum=$((sum + digit))
        # Remove the last digit
        number=$((number / 10))
    done
    echo $sum
}
read -p "Enter a number: " input_number
result=$(calculate_sum_of_digits $input_number)
echo "Sum of digits of $input_number is: $result"
