#!/bin/bash
# This script calculates how many times the words "Netanyahu" and "Gantz" appear in Ynet articles
# Download the main page content
wget -q -O - "https://www.ynetnews.com/category/3082" 

# Extract article URLs
articles=$(grep -oP "https://(www\.)?ynetnews.com/article/[0-9a-zA-Z]+" 3082| sort | uniq)

# Process each URL
for url in $articles; do
    # Get article content
    article_content=$(wget --no-check-certificate -q -O - "$url" 2>/dev/null)
    
    # Count occurrences of 'Netanyahu' and 'Gantz'
    N_count=$(echo "$article_content" | grep -o -i "Netanyahu" | wc -l)
    G_count=$(echo "$article_content" | grep -o -i "Gantz" | wc -l)
    
    # Output the result
    if (( N_count == 0 && G_count == 0 )); then
        echo "$url, -"
    else
        if (( N_count == 0 )); then
            N_count=0
        fi
        if (( G_count == 0 )); then
            G_count=0
        fi
        echo "$url, Netanyahu, $N_count, Gantz, $G_count"
    fi
done
