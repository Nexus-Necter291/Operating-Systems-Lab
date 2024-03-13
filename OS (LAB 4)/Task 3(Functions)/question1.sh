#!/bin/bash

# Function to reverse the number
reverse() {
    local num=$1
    local reversed=$(echo $num | rev)
    echo $reversed
}

# Function to check if the number is a palindrome
palindromeCheck() {
    local num=$1
    local reversed=$2

    if [ "$num" == "$reversed" ]; then
        echo "$num is a palindrome."
    else
        echo "$num is not a palindrome."
    fi
}

# Main script
echo "Main script started..."
echo "Calling function reverse()..."
number=$1
echo ""
echo "function reverse() started..."
reversed=$(reverse $number)
echo "The reverse of $number is $reversed..."
echo ""
echo "Calling function palindromeCheck()..."
echo ""
echo "function palindromeCheck() started..."
palindromeCheck $number $reversed
echo ""
echo "function palindromeCheck() ended..."
echo "function reverse() ended..."
echo ""
echo "main script ending"
