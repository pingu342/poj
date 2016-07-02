#!/bin/sh

#����{�v���O����(https://github.com/mlz000/Poj/blob/master/1015.cpp)
#�����̃v���O����(main.c)

#How to use
# gcc main.c -o dp
# g++ sample.cpp -o sample
# ./verify.sh 2> verify_error.txt

r=100000  #試験回数

for n in `seq 7 7`
do
	for m in `seq 5 5`
	do
		if [ $n -lt $m ]; then
			break;
		fi
		echo "n=$n m=$m"
		perl verify.pl $n $m $r
	done
done

