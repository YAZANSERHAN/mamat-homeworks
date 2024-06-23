#!/bin/bash

site="https://www.ynetnews.com/category/3082"
data=$(wget --no-check-certificate -q -O - $site 2>/dev/null)
articles=$(echo "$data" | grep -oP "https://www.ynetnews.com/article/[0-9a-zA-Z]+")
uniqarticles=$(echo "$articles" | sort | uniq)

words=("Netanyahu" "Gvir" "Lapid" "Gantz")

log_file="script_log.txt"  # Log file to track script execution

for url in $uniqarticles; do 
    # Retrieve article content
    article_content=$(wget --no-check-certificate -q -O - "$url" 2>/dev/null)

    output="$url"
    nonzero=false  # Flag to track if any non zero count is found in the article

    for word in "${words[@]}"; do 
        count=$(echo "$article_content" | grep -o -i "$word" | wc -l)
        if [[ $count -ne 0 ]]; then 
            output="$output, $word, $count"  # Include the name and count in output
            nonzero=true  # Set mention_found to true if any mention is found
        fi
    done

    if ! $nonzero; then
        output="$url, -"  # Set output to include a dash if all zero
    fi

    echo "$output"  

done 
