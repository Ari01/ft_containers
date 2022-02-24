#!/bin/bash

# compile exec debug/non debug FT and STD
if [ "$1" = 'debug' ]
then
	make fclean
	make debug
	./ft > ftout
	./std > stdout
else
	make fclean
	make
	./ft > ftout

	make fclean
	make std
	./std > stdout
fi

echo ""

# print output diff
if diff -y stdout ftout
then
	echo "\n\nTEST OK, OUTPUTS FT AND STD ARE EQUAL"
else
	echo "\nTEST KO, DIFFS FOUND"
fi

echo ""
