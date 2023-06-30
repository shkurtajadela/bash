#!/bin/bash
# Function to compare the output of the grep command with s21_grep
compare_grep() {
    local flag=$1
    local file=$2

    # Run the grep command
    grep "$flag" "h" "$file" > grep_output.txt
    grep "$flag" "1" "$file" > grep_output.txt

    # Run the s21_grep
    ./../s21_grep "$flag" "h" "$file" > s21_grep_output.txt
    ./../s21_grep "$flag" "1" "$file" > s21_grep_output.txt

    # Compare the outputs
    diff grep_output.txt s21_grep_output.txt 
    if [[ $? -eq 0 ]]; then
        echo "PASS: grep $flag $file"
    else
        echo "FAIL: grep $flag $file"
    fi
}

# Function to compare the output of the grep -f command with s21_grep 
compare_grep_f() {
    local pattern_file=$1
    local file=$2

    # Run the grep command
    grep -f "$pattern_file" "$file" > grep_output.txt

    # Run the s21_grep
    ./../s21_grep -f "$pattern_file" "$file" > s21_grep_output.txt

    # Compare the outputs
    diff grep_output.txt s21_grep_output.txt 
    if [[ $? -eq 0 ]]; then
        echo "PASS: grep -f $pattern_file $file"
    else
        echo "FAIL: grep -f $pattern_file $file"
    fi
}

generate_flag_combinations() {
  local combinations=()
  local current_combination=()

  # Recursive function to generate combinations
  generate_combinations_recursive() {
    if [[ $1 -eq ${#flags[@]} ]]; then
      local combination=''
      for flag in "${current_combination[@]}"; do
        combination+="$flag"
      done
      combinations+=("$combination")
      return
    fi

    # Include the flag
    current_combination[$1]=${flags[$1]}
    generate_combinations_recursive $(($1 + 1))

    # Exclude the flag
    current_combination[$1]=''
    generate_combinations_recursive $(($1 + 1))
  }

  # Generate combinations recursively starting from index 0
  generate_combinations_recursive 0

  # Add generated combinations to flags array
  for combination in "${combinations[@]}"; do
    flags+=("$combination")
  done
}

# Flags to test
flags=(e i v c l n h s)

# # Generate flag combinations
generate_flag_combinations
 
# Files to test
files=(1.txt 2.txt 3.txt)

# Iterate over flags and files
for pattern_file in "${flags[@]}"; do
    for file in "${files[@]}"; do
        compare_grep "-$pattern_file" "$file"
    done
done

#Iterate over patternFiles and files
for patternFile in "${files[@]}"; do
    for file in "${files[@]}"; do
        compare_grep_f "$patternFile" "$file"
    done
done

# Clean up temporary files
rm grep_output.txt s21_grep_output.txt