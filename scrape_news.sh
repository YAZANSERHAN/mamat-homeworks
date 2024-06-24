#!/bin/bash
# This script calculates how many times the words "Netanyahu" and "Gantz" appear in Ynet articles

# Download the main page content, extract URLs, and ensure uniqueness
wget -q -O - "https://www.ynetnews.com/category/3082" | \
    grep -oP 'https://(www.)?ynetnews\.com/article/[0-9a-zA-Z]+' | sort | uniq | \
    while read -r url; do
        # Download the article content
        article_content=$(wget --no-check-certificate -q -O - "$url" 2>/dev/null)
        
        # Count occurrences of 'Netanyahu' and 'Gantz' using pipes
        N_count=$(echo "$article_content" | grep -o -i "Netanyahu" | wc -l)
        G_count=$(echo "$article_content" | grep -o -i "Gantz" | wc -l)
        
        # Output the result in the specified format
        if (( N_count == 0 && G_count == 0 )); then
            echo "$url, -"
        else
            echo "$url, Netanyahu, $N_count, Gantz, $G_count"
        fi
    done
