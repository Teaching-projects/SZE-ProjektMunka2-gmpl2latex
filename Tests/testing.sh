#!/bin/bash

FILE=../Tests/std_output.txt
INPF=test_input.mod


if test -f $FILE
then
	rm $FILE
fi

./a.out $INPF >> $FILE
