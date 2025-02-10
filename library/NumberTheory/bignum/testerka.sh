#!/bin/bash

for((i=1;i<1000000;i++))
do
	echo $i > te/seed
	./gen < te/seed > input.in
	./t1 < input.in > te/t1.out
	./t2 < input.in > te/t2.out
	if diff -b te/t1.out te/t2.out
	then
		echo -ne "$i\r"
	else
		echo $i
		break
	fi
done
