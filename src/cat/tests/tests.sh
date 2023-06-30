#!/bin/bash

# Function to compare the output of the cat command with s21_cat
compare_cat() {
    local flag=$1
    local file=$2

    # Run the cat command
    cat "$flag" "$file" > cat_output.txt

    # Run the s21_cat program
    ./../s21_cat "$flag" "$file" > s21_cat_output.txt

    # Compare the outputs
    diff cat_output.txt s21_cat_output.txt
    if [[ $? -eq 0 ]]; then
        echo "PASS: cat $flag $file"
    else
        echo "FAIL: cat $flag $file"
    fi
}

# Flags to test
flags=(-n -e -t -b -s)

# Files to test
files=(1.txt 2.txt 3.txt)

# Iterate over flags and files
for flag in "${flags[@]}"; do
    for file in "${files[@]}"; do
        compare_cat "$flag" "$file"
    done
done

# Clean up temporary files
rm cat_output.txt s21_cat_output.txt
