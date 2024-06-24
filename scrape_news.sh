#!/bin/bash

site="https://www.ynetnews.com/category/3082"
data=$(wget --no-check-certificate -q -O - $site 2>/dev/null)
articles=$(echo "$data" | grep -oP "hhttps://(www.)?ynetnews.com/article/[0-9a-zA-Z]+" 3028| sort| uniq)

for url in $uniqarticles; do 
    # Retrieve article content
    article_content=$(wget --no-check-certificate -q -O - "$url" 2>/dev/null)

    output="$url"
        N_count=$(echo "$article_content" | grep -o -i "Netanyahu" | wc -l)
        G_count=$(echo "$article_content" | grep -o -i "Gantz" | wc -l)
        if(( (( $N_Counter==0 )) && (( $G_Counter==0 )); then 
            output="$url, -"  # Set output to include a dash if all zero
        else 
          echo "$url", "Netanyahu,"" $N_Counter"", Gantz,"" $G_Counter""
            
        fi
done 
