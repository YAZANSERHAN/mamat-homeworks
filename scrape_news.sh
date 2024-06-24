#!/bin/bash
# This script calculates how many times the words "Netanyahu" and "Gantz" appear in Ynet articles

# Download the main page content
main_page_content=$(wget -q -O - "https://www.ynetnews.com/category/3082")

# Extract unique article URLs
articles=$(echo "$main_page_content" | grep -oP 'https://(www\.)?ynetnews.com/article/[0-9a-zA-Z]+' | sort | uniq)

# Process each article URL in parallel to optimize the script
for url in $articles; do
    {
        # Download the article content
        article_content=$(wget --no-check-certificate -q -O - "$url" 2>/dev/null)

        # Count occurrences of 'Netanyahu' and 'Gantz'
        N_count=$(echo "$article_content" | grep -o -i "Netanyahu" | wc -l)
        G_count=$(echo "$article_content" | grep -o -i "Gantz" | wc -l)

        # Output the result in the specified format
        if (( N_count == 0 && G_count == 0 )); then
            echo "$url, -"
        else
            echo "$url, Netanyahu, $N_count, Gantz, $G_count"
        fi
    } &
done

# Wait for all background jobs to complete
wait
