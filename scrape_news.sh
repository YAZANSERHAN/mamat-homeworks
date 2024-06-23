#!/bin/bash

site="https://www.ynetnews.com/category/3082"
data=$(wget --no-check-certificate -q -O - $site 2>/dev/null)
articles=$(echo "$data" | grep -oP "https://www.ynetnews.com/article/[0-9a-zA-Z]+")
uniqarticles=$(echo "$articles" | sort | uniq)

words=("Netanyahu" "Gvir" "Lapid" "Gantz")

for url in $uniqarticles; do 
    article_content=$(wget --no-check-certificate -q -O - "$url")

    output="$url"

    allzero=true  # Reset allzero flag for each article

    for word in "${words[@]}"; do 
        count=$(echo $article_content | grep -o -i "$word" | wc -l)
        if [[ $count -ne 0 ]]; then 
            allzero=false  # Set allzero to false if any word count is non-zero
            output="$output, $word, $count"  # Include the name and count in output
        fi
    done

    if $allzero; then
        output="$url, -"  # Set output to include a dash if no public figure is mentioned
    fi

    echo "$output"  # Print the output line for each article
done
