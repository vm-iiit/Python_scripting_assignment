filep=$1
#echo $filep
if [ ! -f "$filep" ];
then
	echo "invalid file / not a file"
else
	info=$(file -b "$filep")
	#echo $info
	#check=$(grep -ioE "Media|Audio" <<< $info | wc -l)
	#echo $check
	if (( $(grep -ioE "Media|Audio" <<< $info | wc -l)>0 ));
	then
		vlc "$filep"
	elif (( $(grep -ioE "zip|archive|compressed" <<< $info | wc -l)>0 ));
	then
		file-roller "$filep"
	elif (( $(grep -ioE "html" <<< $info | wc -l)>0 ));
	then
		sensible-browser "$filep"
	elif (( $(grep -ioE "source|text" <<< $info | wc -l)>0 ));
	then
		gedit "$filep"
	elif (( $(grep -ioE "image" <<< $info | wc -l)>0 ));
	then
		eog "$filep"
	elif (( $(grep -ioE "PDF" <<< $info | wc -l)>0 ));
	then
		evince "$filep"
	elif (( $(grep -ioE "composite|document" <<< $info | wc -l)>0 ));
	then
		libreoffice "$filep"
	elif (( $(grep -ioE "object" <<< $info | wc -l)>0 ));
	then
		./"$filep"
	else
		echo "can't find a suitable program to open the file"
	fi
fi