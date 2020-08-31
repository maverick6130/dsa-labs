#!/bin/bash
for i in $(seq 1 $1)
do
	touch input.txt
	touch output.txt
	./makecase $2 $3 > input.txt
	./a.out < input.txt > output.txt
	if [ "Correct" != $(./checker input.txt output.txt) ];
	then
		echo "Incorrect implementation!"
		exit 1
	fi
	rm input.txt
	rm output.txt
done
echo "Correct"