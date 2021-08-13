#!/bin/bash

#This file is used to test the functioning of the dictionary

g++ Dictionary.cpp main.cpp -o executable
words=$( cat /usr/share/dict/words | egrep '^[a-z]+$' | head -70 )
queries=""
for word in $words
do
    queries="$queries ?$word"
done
words2=$( cat /usr/share/dict/words | egrep '^[a-z]+$' | head -4 )
deletions=""
words3=$( cat /usr/share/dict/words | egrep '^[a-z]+$' | head -6 | tail -2 )
for word in $words3
do
    deletions="$deletions !$word"
done
input="$words $queries $words2 $queries $deletions $queries #"
echo $input
echo $input | ./executable