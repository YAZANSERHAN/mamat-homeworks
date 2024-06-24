#!/bin/bash
# This script calculates how many times the words "Netanyahu" and "Gantz" appear in Ynet articles

# Download the main page content
wget -q -O ynetnews "https://www.ynetnews.com/category/3082"

# Extract article URLs
articles=$(grep -oP "https://(www.)?ynetnews.com/article/[0-9a-zA-Z]+" ynetnews| sort | uniq)

# Download and process each article
for url in $articles; do
    # Get article content
    article_content=$(wget --no-check-certificate -q -O - "$url" 2>/dev/null)
    
    # Count occurrences of 'Netanyahu' and 'Gantz'
    N_count=$(echo "$article_content" | grep -o -i "Netanyahu" | wc -l)
    G_count=$(echo "$article_content" | grep -o -i "Gantz" | wc -l)
    
    # Output the result
    if (( (( N_count == 0 )) && (( G_count == 0 )) )); then
        echo "$url"", -"
    else
        echo "$url,"" Netanyahu,"" $N_Count"", Gantz,"" $G_Count""
    fi
done
