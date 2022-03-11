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
if diff -y stdout ftout
then
	echo "TEST OK, OUTPUTS FT AND STD ARE EQUAL"
else
	echo "TEST KO, DIFFS FOUND"
fi

echo ""
