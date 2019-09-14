#!/bin/bash
pre="https://darksky.net/forecast/"
post="/si12/en"
echo -n "Enter longtitutde :"
read "long"
echo -n "Enter latitutde :"
read "lat"
echo -n "Temperature is :"
touch __temp.txt
curl -sS ${pre}${long},${lat}${post} > __temp.txt
grep -E "*\<span class\>*" < __temp.txt | grep -E "*summary swap\>*" | grep -oE "[[:digit:]]{2}.{1}" | tr -s '\n' ' '
echo -n "and weather is"
grep -oE "summary swap.*\&nbsp.*" < __temp.txt | grep -oE "\;.*\." | sed 's/;/ /g'
rm __temp.txt 
exit