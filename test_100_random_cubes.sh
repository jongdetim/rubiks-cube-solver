#!/bin/bash

RED='\033[0;91m'
GREEN='\033[0;92m'
NC='\033[0m'

for i in {0..100}
do
	    echo -e "$GREEN\nepoch $i\n$NC"
	        ./rubik -v -r 50
		    if [ $? -eq 139 ]; then echo "$RED Segfault$NC"; exit 1; fi
done
