#!/bin/bash

# Download main page
wget -q -O ynetnews "https://www.ynetnews.com/category/3082"

# Extract URLs
articles=$(grep -oP "https://www.ynetnews.com/article/[0-9a-zA-Z]+" ynetnews | sort | uniq)

# Process each URL
for url in $articles; do
    # Get article content
    article_content=$(wget --no-check-certificate -q -O - "$url" 2>/dev/null)
    
    # Count keywords
    N_count=$(echo "$article_content" | grep -o -i "Netanyahu" | wc -l)
    G_count=$(echo "$article_content" | grep -o -i "Gantz" | wc -l)
    
    # Output result
    if (( N_count == 0 && G_count == 0 )); then
        echo "$url, -"
    else
        echo "$url, Netanyahu: $N_count, Gantz: $G_count"
    fi
done
