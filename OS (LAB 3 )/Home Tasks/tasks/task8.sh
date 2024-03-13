#!/bin/bash

# Define the roll number
roll_number="192"

# Define a number for comparison
comparison_number=2000

# Perform relational operations
result_equal=$(( roll_number == "192" ))  # Equal to
result_not_equal=$(( roll_number != "191" ))  # Not equal to
result_greater_than=$(( roll_number > comparison_number ))  # Greater than
result_less_than=$(( roll_number < comparison_number ))  # Less than
result_greater_than_or_equal=$(( roll_number >= comparison_number ))  # Greater than or equal to
result_less_than_or_equal=$(( roll_number <= comparison_number ))  # Less than or equal to

# Print the roll number and results of operations
echo "Roll number: $roll_number"
echo "Is roll number equal to '192'? $result_equal"
echo "Is roll number not equal to '191'? $result_not_equal"
echo "Is roll number greater than $comparison_number? $result_greater_than"
echo "Is roll number less than $comparison_number? $result_less_than"
echo "Is roll number greater than or equal to $comparison_number? $result_greater_than_or_equal"
echo "Is roll number less than or equal to $comparison_number? $result_less_than_or_equal"

