// 遠く離れたFrobniaという国では、裁判の判決は一般人で構成された陪審員により決定される
// 裁判が始まる度に審査員は次のように選ばれる
// 2つの組織(prosecutionとdefence)が陪審員の候補である人物に0から20のグレードを割り当てる
// 20が陪審員に最も適していることを表す
// このグレードに基いて裁判官が陪審員を選ぶ
// 陪審員の選択は2つの組織にとって満足がいくものでなければならない
// 候補者をn人、陪審員をm人、2つの組織がi番目の候補者に割り当てたグレードをpi,diとする
// 候補者の集合{1,...,n}から選ばれたm人の部分集合をJとする
// Jに属する候補者のグレードの合計をD(J),P(J)とする
// D(J)=SUM(dk)
// P(J)=SUM(pk)
// ここでkはJに所属する候補者の番号を表す
// |D(J)-P(J)|が最小となるJが最適な選択である
// このようなJが複数存在する場合、D(J)+P(J)が最大となるJが最適な選択である
//
//
// 入力:
//
// 4 2 
// 1 2 
// 2 3 
// 4 1 
// 6 2 
// 0 0
//
// 最初の行はn, m
// ここで、
//   1 <= n <= 200
//   1 <= m <= 20
//   m <= n
// 次のn個の行はpiとdi(i=1,..,n)
// 次の空行は次のラウンドの開始
// もし0 0なら最終ラウンド
//
//
// 出力:
//
// Jury #1 
// Best jury has value 6 for prosecution and value 4 for defence: 
//  2 3 
// 
// 最初の行はラウンドの番号
// 次の行はD(J)とP(J)
// 次の行は選ばれた候補者の番号(昇順)
// 各ラウンドは空行で分割
//
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if 1

int n, m, pi[200], di[200];
int dp[21][801];
int sel[21][801][21]; //di-piの範囲はdi,piが最大20なので-20〜20の範囲、よってD(J)-P(J)の範囲は-20m〜20mで、mは最大20なので-400〜400となり、801パターンありうる

void print()
{
	int i, j;
	for (i=1; i<=m; i++)
		for (j=0; j<801; j++)
			if (dp[i][j])
				printf("%d,%d : %d\n", i, j-400, dp[i][j]);
	printf("\n");
}

void update(int num, int sub, int sum_dp, int i, int pre[])
{
	int j;
	if (dp[num][sub] < sum_dp) {
		dp[num][sub] = sum_dp;
		for (j=1; j<num; j++)
			sel[num][sub][j] = pre[j];
		sel[num][sub][j] = i;
	}
}

void search()
{
	int i, j, k, d, p;
	for (i=1; i<=n; i++) {
		d = di[i-1];
		p = pi[i-1];
		for (j=m; j>=2; j--) {
			for (k=0; k<801; k++) {
				if (dp[j-1][k] != 0) {
					//dp[j][k+d-p] = max(dp[j][k+d-p], dp[j-1][k]+d+p);
					update(j, k+d-p, dp[j-1][k]+d+p, i, sel[j-1][k]);
				}
			}
		}
		//dp[1][d-p+400] = max(dp[1][d-p+400], d+p);
		update(1, d-p+400, d+p, i, NULL);
		//print();
	}
}

int main()
{
	int i, l, no;
	for (no=1; scanf("%d %d",&n,&m) && n>0; no++) {
		for (i=0; i<n; i++)
			scanf("%d %d", &pi[i], &di[i]);
		memset(dp, 0, sizeof(dp));
		memset(sel, 0, sizeof(sel));
		search();
		for (int k = 0; k <= 400; ++k) { // |D(J)-P(J)|が0,1,2,...の順で検索
			if (dp[m][k + 400] != 0 || dp[m][400 - k] != 0) {
				k = (dp[m][k + 400] > dp[m][400 - k]) ? k + 400 : 400 - k;
				int he = dp[m][k];
				int sum_d=0, sum_p=0, sub_pd=0;
				for (l=1; l<=m; l++) {
					sum_p += pi[sel[m][k][l]-1];
					sum_d += di[sel[m][k][l]-1];
					sub_pd += di[sel[m][k][l]-1]-pi[sel[m][k][l]-1];
				}
				printf("Jury #%d\nBest jury has value %d for prosecution and value %d for defence:\n", no, sum_p, sum_d);
				for (l=1; l<=m; l++)
					printf(" %d", sel[m][k][l]);
				printf("\n\n");
				break;
			}
		}
	}
}

#endif

/*
test

4 2
1 2
2 3
4 1
6 2

4 2
1 2
2 3
4 1
6 2
0 0

200 20
7 7
2 20
13 20
9 8
8 1
6 2
0 20
0 5
16 4
4 10
18 19
15 14
1 3
6 9
14 16
4 17
14 13
8 12
7 1
0 18
13 14
7 0
2 5
11 4
6 16
2 5
7 1
7 17
9 14
6 7
19 7
12 17
8 1
0 0
9 10
7 13
19 13
0 1
14 12
20 5
6 10
0 7
8 17
18 17
3 3
18 8
11 16
12 20
13 12
11 3
12 0
11 17
20 14
4 3
12 6
2 2
17 18
3 20
16 10
2 14
6 4
12 13
16 18
20 1
7 12
19 10
10 1
1 12
15 1
6 2
20 9
8 12
10 8
11 4
5 19
8 7
3 3
3 11
1 20
10 18
6 14
8 2
0 7
15 14
1 1
20 15
4 12
4 10
20 3
19 12
13 13
8 6
8 3
16 10
19 4
8 11
16 18
15 2
16 20
6 9
0 13
8 14
18 15
10 5
20 19
0 10
17 11
14 0
6 4
19 15
16 5
11 18
18 1
1 0
3 7
16 8
8 7
20 6
4 18
1 14
17 4
9 18
9 16
2 1
9 9
15 11
0 2
12 12
15 17
0 16
20 7
2 0
13 19
10 4
9 3
18 0
14 14
5 15
15 6
14 12
4 2
13 18
2 8
13 3
8 14
3 1
3 7
11 15
14 2
15 0
20 10
16 11
15 18
5 0
19 5
15 15
20 8
2 18
8 4
20 6
12 3
8 5
16 1
7 14
0 8
18 18
15 10
15 3
13 17
1 9
17 1
3 15
19 11
12 7
19 0
11 17
8 2
0 10
0 15
18 10
20 0
1 19
16 6
9 14
6 12
12 12
6 1
14 1
12 11
5 12
9 10
12 7
0 0
13 13
8 4
9 8
2 8
13 7
8 4
20 16

$ gcc test.c -o test
$ ./test | ./main.out

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

o : Best jury has value 111 for prosecution and value 111 for defence:
     2 4 6 7 8 9 10 13 15 16

x : Best jury has value 112 for prosecution and value 112 for defence:
     4 6 9 10 11 12 13 14 15 16

          16 10
   1:-4   0 4     4
+  2:-10  7 17    24
   3:9    12 3    15
+* 4:9    20 11   31
   5:-3   1 4     5
+* 6:8    14 6    20
+  7:-7   0 7     7
+  8:16   16 0    16
+* 9:4    17 13   30
+*10:-6   9 15    24
 *11:13   13 0    13
 *12:2    8 6     14
+*13:1    8 7     15
 *14:-16  3 19    22
+*15:-8   9 17    26
+*16:-7   11 18   29

*/

