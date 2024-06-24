#!/bin/bash
# This script calculates how many times the words "Netanyahu" and "Gantz" appear in Ynet articles

# Download the main page content
wget -q -O ynetnews "https://www.ynetnews.com/category/3082"

# Extract article URLs
articles=$(grep -oP "https://(www\.)?ynetnews.com/article/[0-9a-zA-Z]+" ynetnews | sort | uniq)

# Download all articles
wget --no-check-certificate -q -i <(echo "$articles")

# Process each URL
for url in $articles; do
    # Extract the article filename from the URL
    filename=$(echo "$url" | grep -o '[^/]\+$')

    # Count occurrences of 'Netanyahu' and 'Gantz' in the article content
    N_count=$(grep -o -i "Netanyahu" "$filename" | wc -l)
    G_count=$(grep -o -i "Gantz" "$filename" | wc -l)

    # Output the result
    if (( N_count == 0 && G_count == 0 )); then
        echo "$url, -"
    else
        echo "$url, Netanyahu, $N_count, Gantz, $G_count"
    fi
done
