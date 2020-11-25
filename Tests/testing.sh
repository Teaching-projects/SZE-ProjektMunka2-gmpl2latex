#!/bin/bash

FILE=./Tests/std_output.txt
INPF=./Tests/test_input.mod


if test -f $FILE
then
	rm $FILE
fi

./a.out $INPF --createjson var.json >> $FILE
./a.out $INPF --readjson ./Tests/modvar.json --outputtex texOutput.tex
