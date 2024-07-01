#!/bin/bash
# This script calculates how many times the words "Netanyahu" and "Gantz" appear in Ynet articles

# Download the main page content
main_page_content=$(wget -q -O - "https://www.ynetnews.com/category/3082")

# Extract unique article URLs
articles=$(echo "$main_page_content" | grep -oP 'https://(www\.)?ynetnews.com/article/[0-9a-zA-Z]+' | sort | uniq)

# Function to process each article
process_article() {
    url="$1"
    
    # Download the article content
    article_content=$(wget --no-check-certificate -q -O - "$url" 2>/dev/null)
    
    # Count occurrences of 'Netanyahu' and 'Gantz' using awk
    echo "$article_content" | awk -v url="$url" '
    BEGIN {
        N_count = 0
        G_count = 0
    }
    {
        N_count += gsub(/Netanyahu/, "", $0)
        N_count += gsub(/netanyahu/, "", $0)
        G_count += gsub(/Gantz/, "", $0)
        G_count += gsub(/gantz/, "", $0)
    }
    END {
        if (N_count == 0 && G_count == 0) {
            print url ", -"
        } else {
            print url ", Netanyahu, " N_count ", Gantz, " G_count
        }
    }'
}

export -f process_article

# Process articles in parallel using xargs
echo "$articles" | xargs -n 1 -P 10 bash -c 'process_article "$@"' _

# Wait for all background jobs to complete
wait
