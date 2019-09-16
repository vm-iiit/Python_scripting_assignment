filepath=$1
if [ ! -f $filepath ];
then
	echo "Invalid file/path"
	exit
else
	if(($(file -b $filepath | grep -oE "archive|compressed|zip|rar" | wc -l) == 0));
	then
		echo "not an archive"
		exit
	else
		path=$( grep -oE ".*\/" <<< $filepath)
		#echo "path $path"
		cd $path
		ext=$( grep -oE "\.[[:alnum:]]*$" <<< "$filepath"  | grep -oE "[[:alnum:]]*")
		filename=${filepath##*/}
		echo "filename :$filename"
		echo "extension :$ext"
		if [ "$ext" = "gz" ];
		then
			if (( $(grep -oE "tar" <<< "$filename" | wc -l) >0));
			then
				tar -xvf "$filename"	
			else
				gzip -d "$filename"
			fi
		elif [ "$ext" = "xz" ];
		then
			tar -xf "$filename"
		elif [ "$ext" = "bz2" ];
		then
			if (( $(grep -oE "tar" <<< "$filename" | wc -l) >0));
			then
				tar -xjvf "$filename"	
			else
				bzip2 -d "$filename"
			fi
		elif [ "$ext" = "7z" ];
		then
			7z e "$filename"
		elif [ "$ext" = "zip" ];
		then
			unzip "$filename"
		elif [ "$ext" = "tgz" ];
		then
			tar -xzvf "$filename"
		else
			tar -jxvf "$filename"
		fi
	fi
	echo "extracted"
fi