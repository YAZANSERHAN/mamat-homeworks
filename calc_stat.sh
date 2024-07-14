#!/bin/bash


if [ $# -ne 1 ]; then
    echo "Wrong number of arguments" >&2
    exit 1
fi

if ! [[ "$1" =~ ^[0-9]{6}$ ]]; then
    echo "Course not found" >&2
    exit 1
fi

courseNo=$1
found=false

for dir in */; do

  dir=${dir%/}
  
  if [[ $dir = $courseNo ]]; then
    found=true
  fi
done

if [ "$found" = false ]; then
    echo "Course not found" >&2
    exit 1
fi

# checks if stat dir exists, and it deletes it if it does
stat_dir="$courseNo"_stat

if [ -d "$stat_dir" ]; then
  rm -rf "$stat_dir"
fi

# creates new stat dir
mkdir "$stat_dir"

./hist $courseNo/grades.txt > $stat_dir/histogram.txt

mean="./mean $courseNo/grades.txt"
median="./median $courseNo/grades.txt"
min="./min $courseNo/grades.txt"
max="./max $courseNo/grades.txt"

echo -e "$mean\t$median\t$min\t$max" > $stat_dir/statistics.txt
