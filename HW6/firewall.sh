#!/bin/bash
packets=$(cat | tr -d ' ')

# we will go on while loop over the all rules
while read line
do
	# delete "," and spaces in the rule line
	rule=$(echo "$line" | tr -d ',' | tr -d ' ' )
	
	# delete the comments in the rule line
	rule=$(echo "$rule" | sed -e 's/#.*//' ) 
	
	# replace the field with *field in order to split the rule
	rule=$(echo "$rule" | sed -e 's/dst-ip/*dst-ip/g')
	rule=$(echo "$rule" | sed -e 's/src-port/*src-port/g')
	rule=$(echo "$rule" | sed -e 's/dst-port/*dst-port/g')
	
	if [[ "$rule" != "" ]]; then
		SI=$(echo $rule | awk -F* '{print $1}')	
		DI=$(echo $rule | awk -F* '{print $2}')	
		SP=$(echo $rule | awk -F* '{print $3}')	
		DP=$(echo $rule | awk -F* '{print $4}')
		
		
		collected_pkts+=$(echo "$packets" | \
			./firewall.exe "$SI" | \
			./firewall.exe "$DI" | \
			./firewall.exe "$SP" | \
			./firewall.exe "$DP")
		collected_pkts+="\n"
	fi
done < "$1"

# format and sort the collected packets to print them 
echo -e "$collected_pkts" | sed "s/src-ip/\n&/g" | sed '/^$/d' | sort -u
