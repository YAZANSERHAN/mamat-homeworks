#!/bin/bash

site="https://www.ynetnews.com/category/3082"

data=$(wget --no-check-certificate -q -O - $site 2>/dev/null)

articles=$(echo "$data" | grep -oP "https://www.ynetnews.com/article/[0-9a-zA-Z]+")

uniqarticles=$(echo "$articles" | sort | uniq)

words=("Netanyahu" "Gvir" "Lapid" "Gantz")

articles_dir="articles"

mkdir -p $articles_dir

for url in $uniqarticles; do 

	article_content=$(wget --no-check-certificate -q -O - "$url")

	
	output="$url"

	allzero=true

	for word in "${words[@]}"; do 
		count=$(echo $article_content | grep -o -i "$word" | wc -l)
		if [[ $count -ne 0 ]]; then 
			allzero=false
		fi
		output="$output, $word, $count"
	done

if ! $allzero; then
	output="$url, -"
fi

echo "$output"
done
