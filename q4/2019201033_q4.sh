echo -n "Enter the password :"
read -s passwd
echo
#echo $passwd
len=${#passwd}
nums=$(grep -oE "[[:digit:]]" <<< $passwd | wc -l)
#echo $nums
chars=$(grep -oE "[@#$%&*+-=]" <<< $passwd | wc -l)
#echo "length is $len"
let iupb=len-4
if ((len <8 | nums < 1 | chars<1)); then
	echo "weak password"
else
	for i in `seq 0 $iupb`;
	do
		#echo "value of i :$i"
		((upb=len-i))
		for j in `seq 4 $upb`;
		do
			#echo "value of j :$j"
			#echo "$i $j"
			substr=${passwd:i:j}
			#echo $substr
			occ=$(grep -o $substr /usr/share/dict/american-english /usr/share/dict/american-english | wc -l)
			#echo "occurences $occ"
			if((occ>=1));
			then
				echo "weak password"
				exit
			fi
		done
	done
	echo "strong password"
fi
