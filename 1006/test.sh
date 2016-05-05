#!/bin/sh
while :
do
	p=$(($RANDOM % 366))
	e=$(($RANDOM % 366))
	i=$(($RANDOM % 366))
	d=$(($RANDOM % 366))
	echo $p $i $i $d > tmp
	# お手本の答え
	cat tmp | ./sample > tmp0
	# 自分の答え
	cat tmp | ./main > tmp1
	# 答え合わせ
	if diff -q tmp0 tmp1 >/dev/null ; then
		cat tmp
	else
		cat tmp
		cat tmp0
		cat tmp1
		break
	fi
done

# プログラムは1回のscanfで終了するように変更しておくこと
