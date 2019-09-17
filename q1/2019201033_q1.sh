echo "Enter 1 for weather by city and 2 for weather by lat/long"
read choice
pre="https://darksky.net/forecast/"
post="/si12/en"
if [ $choice -eq 2 ];
then
	echo -n "Enter longtitutde :"
	read "long"
	echo -n "Enter latitutde :"
	read "lat"
	echo -n "Temperature is :"
	touch __temp.txt
	curl -sS ${pre}${lat},${long}${post} >> __temp.txt
	grep -E "*\<span class\>*" < __temp.txt | grep -E "*summary swap\>*" | grep -oE "[[:digit:]]{2}.{1}" | tr -s '\n' ' '
	echo -n "and weather is"
	grep -oE "summary swap.*\&nbsp.*" < __temp.txt | grep -oE "\;.*\." | sed 's/;/ /g'
	rm __temp.txt 
	exit
else
	echo -n "Enter city name :"
	read city
	city=$(echo $city | sed -e "s/\b\(.\)/\u\1/g" | sed -e 's/ /_/g' )
	echo -n "$city's"
	prefix="https://en.wikipedia.org/wiki/"
	#echo ${prefix}"${city}"
	curl -sS ${prefix}"${city}" > __tmp.txt
	lat=$(grep -ohE -m 1 \{\"lat\"\:[[:digit:]\.]*\,{1} < __tmp.txt | grep -oE [[:digit:]]+\.[[:digit:]]+)
	lon=$(grep -ohE -m 1 \,\"lon\"\:[[:digit:]\.]*\}{1} < __tmp.txt | grep -oE [[:digit:]]+\.[[:digit:]]+)
	lat=${lat:0:6}
	lon=${lon:0:6}
	echo -n " latitude is $lat "
	echo "and longtitude is $lon"
	rm __tmp.txt
	echo -n "Temperature is :"
	touch __temp.txt
	curl -sS ${pre}${lat},${lon}${post} > __temp.txt
	grep -E "*\<span class\>*" < __temp.txt | grep -E "*summary swap\>*" | grep -oE "[[:digit:]]{2}.{1}" | tr -s '\n' ' '
	echo -n "and weather is"
	grep -oE "summary swap.*\&nbsp.*" < __temp.txt | grep -oE "\;.*\." | sed 's/;/ /g'
	rm __temp.txt
fi