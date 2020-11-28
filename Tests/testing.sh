#!/bin/bash

FILE=./Tests/std_output.txt
INPF=./Tests/test_input.mod


if test -f $FILE
then
	rm $FILE
fi

./gmpl2latex $INPF --createjson var.json
./gmpl2latex $INPF --readjson ./Tests/modvar.json --outputtex texOutput.tex
