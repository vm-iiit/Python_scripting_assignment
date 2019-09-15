filep=$1
#echo $filep
if [ ! -f "$filep" ];
then
	echo "invalid file"
else
	info=$(file -b "$filep")
	#echo $info
	#check=$(grep -ioE "Media|Audio" <<< $info | wc -l)
	#echo $check
	if (( $(grep -ioE "Media|Audio" <<< $info | wc -l)>0 ));
	then
		vlc "$filep"
	elif (( $(grep -ioE "source|text" <<< $info | wc -l)>0 ));
	then
		gedit "$filep"
	fi
fi