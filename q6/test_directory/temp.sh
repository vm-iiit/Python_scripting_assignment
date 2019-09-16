args=$@
nargs=$#
echo $args
subargs=$(echo ${@:2})
echo $subargs
for var in $@;
do
	echo "$var"
done