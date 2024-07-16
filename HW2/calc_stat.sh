#!/bin/bash

# Check if the number of arguments is exactly 1
if [ $# -ne 1 ]; then
    echo "Wrong number of arguments" >&2
    exit 1
fi

# Check if the argument is a 5 or 6-digit number
if ! [[ "$1" =~ ^[0-9]{5,6}$ ]]; then
    echo "Course not found" >&2
    exit 1
fi

courseNo=$1

# Check if the course file exists
if [ ! -f "$courseNo" ]; then
    echo "Course not found" >&2
    exit 1
fi

# Generate a histogram from the grades and save it to a histogram file
./hist "$courseNo" > "histogram_$courseNo.txt"

# Calculate statistical values
mean=$(./mean "$courseNo")
median=$(./median "$courseNo")
min=$(./min "$courseNo")
max=$(./max "$courseNo")

# Write the statistics to a file
echo -e "Mean: $mean\nMedian: $median\nMin: $min\nMax: $max" > "statistics_$courseNo.txt"
