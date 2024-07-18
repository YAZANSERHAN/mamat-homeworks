#!/bin/bash

# Ensure correct number of arguments
if [[ $# -lt 1 || $# -gt 2 ]]; then 
   echo "Wrong number of arguments" >&2
   exit 1
fi 

course_file="$1"
stat_dir="${1}_stat"

# Ensure the course file exists
if [[ ! -f "$course_file" ]]; then
   echo "Course not found" >&2
   exit 1
fi 

# Create the statistics directory
if [[ -d "$stat_dir" ]]; then
   rm -r "$stat_dir"
fi 
mkdir -p "$stat_dir"

# Compile the C programs
gcc -g -Wall hist.c -o hist.exe
gcc -g -Wall median.c -o median.exe
gcc -g -Wall mean.c -o mean.exe
gcc -g -Wall min.c -o min.exe
gcc -g -Wall max.c -o max.exe

# Verify the compilation was successful
[[ ! -x hist.exe || ! -x median.exe || ! -x mean.exe || ! -x min.exe || ! -x max.exe ]] && { echo "Compilation failed" >&2; exit 1; }

# Set the bin size if provided, otherwise default to 10
if [[ $# -eq 2 ]]; then
    bin_size=$2
else
    bin_size=10
fi

# Generate the histogram
./hist.exe "$course_file" "$bin_size" > "$stat_dir/histogram.txt"

# Calculate statistics and write them to statistics.txt with tab-separated values
echo -n -e "$(./mean.exe "$course_file")\t" > "$stat_dir/statistics.txt"
echo -n -e "$(./median.exe "$course_file")\t" >> "$stat_dir/statistics.txt"
echo -n -e "$(./min.exe "$course_file")\t" >> "$stat_dir/statistics.txt"
echo -e "$(./max.exe "$course_file")" >> "$stat_dir/statistics.
