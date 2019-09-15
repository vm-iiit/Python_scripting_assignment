#check valid folder
if [ ! -d $1 ]; then
	echo "Directory not found! exiting."
	exit
fi
#remove trailing /
string=$1
let len=${#string}
#echo $len
#echo ${string:${len}-1}
lastchar=${string:${len}-1}
#echo $lastchar
if [ "$lastchar" = "/" ];
then
	string=${string:0:$len-1}
fi
#echo $string
if [ $2 = "all" ]; then
	#echo "qwerty"
	for var in $(ls -ltr $string | grep -E "^\-.*" | grep -oE "[[:alnum:]]*$" ); do
		#echo $var
		mkdir -p $string/$var
		mv $string/*.var $string/$var/
	done
	#echo "names of files"
	#for file in $( ls -A1 $string | grep -E "^\-.*" | grep -oE "[ ]{1}[[:alnum:]\.[:punct:]]*$" );
	#do
	#	echo -n $file
	#	echo -n " "
	#	ext=$(echo $file | grep -oE "[[:alnum:]]*$")
	#	#echo " with extension $ext"
		
	#done
	#file without extension
	#if [ $(ls -ltr $1 | grep -E "^\-.*" | wc -l) -gt 0 ]; then
	#	echo "files left"
	#fi
else
	for ftype in ${@:2};
	do
		mkdir -p $string/$ftype
		mv $string/*.$ftype $string/$ftype/
	done
fi