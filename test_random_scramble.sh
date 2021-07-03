#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

for i in {0..100}
do
    echo "$GREEN\nepoch $i\n$NC"
    ./rubik ""
    if [ $? -eq 139 ]; then echo "$RED Segfault$NC"; exit 1; fi
done