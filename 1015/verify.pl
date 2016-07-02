
if (@ARGV!=3) {
	exit 1;
}

my $test  = "test";		#testデータ生成器
my $prog1 = "sample";	#お手本プログラム(https://github.com/mlz000/Poj/blob/master/1015.cpp)
my $prog2 = "dp";		#自分のプログラム(main.c)

my $n = $ARGV[0];	#n
my $m = $ARGV[1];	#m
my $r = $ARGV[2];	#round

my $s = 1;  #rand seed

for (my $i=0; $i<$r; $i++) {

	#n,m,sのパラメーターでtestデータを1roundだけ生成し、お手本プログラムと自分のプログラムに入力する
	#そのtestデータと、お手本プログラムと自分のプログラムの出力を、ログファイルに出力する
	`./$test -n $n -m $m -r 1 -s $s | tee $test.log | ./$prog1 | tee $prog1.log`;
	`./$test -n $n -m $m -r 1 -s $s | ./$prog2 | tee $prog2.log`;
	$s++;

	open (TEST_LOG,  $test  . ".log");
	open (PROG1_LOG, $prog1 . ".log");
	open (PROG2_LOG, $prog2 . ".log");

	@prog1_log = <PROG1_LOG>;
	@prog2_log = <PROG2_LOG>;

	if ($prog1_log[1] ne $prog2_log[1]) {
		#進行状況表示
		printf("x");

		#お手本と結果が異なる場合、標準エラー出力に結果を出力
		printf(STDERR "\n");
		while (<TEST_LOG>) {
			printf STDERR;
		}
		printf(STDERR "$prog1 : $prog1_log[1]");
		printf(STDERR "$prog2 : $prog2_log[1]");
	} else {
		#進行状況表示
		printf(".");
	}

	close (TEST_LOG);
	close (PROG1_LOG);
	close (PROG2_LOG);
}

printf("\n");

=pod

お手本プログラム(https://github.com/mlz000/Poj/blob/master/1015.cpp)と結果が合わない場合あり
お手本プログラムのほうが間違っていると思われる
例えば、、、

16 10
0 4
7 17
12 3
20 11
1 4
14 6
0 7
16 0
17 13
9 15
13 0
8 6
8 7
3 19
9 17
11 18

を入力した場合

お手本 : Best jury has value 111 for prosecution and value 111 for defence:
          2 4 6 7 8 9 10 13 15 16

自分   : Best jury has value 112 for prosecution and value 112 for defence:
          4 6 9 10 11 12 13 14 15 16

だけど、、、

お手本のほうは、
D+P=222
D-P=0

自分のほうは、
D+P=224
D-P=0

D-Pは同じでD+Pは自分のほうが大きいので、自分のほうが正しい

=cut
