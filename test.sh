#!/bin/bash

# compile exec FT and STD
make fclean

if [ "$1" = 'std' ]
then
	make CPPFLAGS="-D STD=1 -D TIME=1" std
	./std > stdout
elif [ "$1" = 'ft' ]
then
	make CPPFLAGS="-D STD=0 -D TIME=1" ft
	./ft > ftout
elif [ "$1" = 'provided' ]
then
		make provided
		./provided 1
else
	if [ "$1" = 'time' ]
	then
		make CPPFLAGS=" -D STD=1 -D TIME=1" std
		./std > stdout

		make clean
		make CPPFLAGS=" -D STD=0 -D TIME=1" ft
		./ft > ftout

	elif [ "$1" = 'sanitize' ]
	then
		make CPPFLAGS=" -D STD=1 -D SANITIZE=1" std
		valgrind ./std > stdout

		make clean
		make CPPFLAGS=" -D STD=0 -D SANITIZE=1" ft
		valgrind ./ft > ftout
	else
		make CPPFLAGS=" -D STD=1" std
		./std > stdout

		make clean
		make CPPFLAGS=" -D STD=0" ft
		./ft > ftout
	fi

	echo ""

	# print output diff
	if $(diff -y --suppress-common-lines stdout ftout > diff_output)
	then
		echo "DIFF TEST OK"
	else
		echo "DIFF TEST KO, diffs found"
	fi

	# grep TEST KO in tests
	if grep "TEST KO" stdout ftout
	then
		echo "GREP TEST KO, some tests ko'd"
	else
		echo "GREP TEST OK"
	fi
fi
