#!/bin/bash

# compile exec FT and STD
make fclean

if [ "$1" = 'debug' ]
then
	make debug
	./ft > ftout
	./std > stdout
	else if [ "$1" = 'time' ]
	then
		make time
		./ft > ftout
		./std > stdout
		else if [ "$1" = 'sanitize' ]
		then
			make sanitize
			valgrind ./ft > ftout
			valgrind ./std > stdout
		else
			make fclean
			make
			./ft > ftout

			make clean
			make std
			./std > stdout
		fi
	fi
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
