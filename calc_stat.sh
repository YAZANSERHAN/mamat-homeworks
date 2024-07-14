#!/bin/bash

# Check the number of arguments
if [ $# -ne 1 ]; then
    echo "Wrong number of arguments" >&2
    exit 1
fi

# Validate the course number format
if ! [[ "$1" =~ ^[0-9]{6}$ ]]; then
    echo "Course not found" >&2
    exit 1
fi

courseNo=$1
found=false

# Search for the course directory
for dir in */; do
  dir=${dir%/}
  if [[ $dir == $courseNo ]]; then
    found=true
    break
  fi
done

if [ "$found" = false ]; then
    echo "Course not found" >&2
    exit 1
fi

# Check if the statistics directory exists and remove it if it does
stat_dir="${courseNo}_stat"
if [ -d "$stat_dir" ]; then
  rm -rf "$stat_dir"
fi

# Create a new statistics directory
mkdir "$stat_dir"

# Generate histogram
./hist "$courseNo/grades.txt" > "$stat_dir/histogram.txt"

# Calculate statistics and store the output
mean=$(./mean "$courseNo/grades.txt")
median=$(./median "$courseNo/grades.txt")
min=$(./min "$courseNo/grades.txt")
max=$(./max "$courseNo/grades.txt")

# Check if all commands executed successfully
if [ $? -ne 0 ]; then
    echo "Error calculating statistics" >&2
    exit 1
fi

# Write statistics to the file
echo -e "$mean\t$median\t$min\t$max" > "$stat_dir/statistics.txt"
