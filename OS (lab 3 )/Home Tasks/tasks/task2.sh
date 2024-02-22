#!/bin/bash

echo "Welcome to the message combiner script!"
read -p "Please enter your name: " name
read -p "Please enter your age: " age
read -p "Please enter your favorite color: " color

message="Hello, $name! You are $age years old and your favorite color is $color."

echo "$message"

