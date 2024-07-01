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

        # Use awk to count occurrences of 'Netanyahu' and 'Gantz'
        awk -v url="$url" '
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
        }
        ' <<< "$article_content"
    } &
done

# Wait for all background jobs to complete
wait
