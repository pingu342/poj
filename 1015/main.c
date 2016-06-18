// 遠く離れたFrobniaという国では、裁判の判決は一般人で構成された陪審員により決定される
// 裁判が始まる度に審査員は次のように選ばれる
// 2つの組織(prosecutionとdefence)が陪審員の候補である人物に1から20のグレードを割り当てる
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

int n, m, pi[200], di[200], poo[200], sel[21], sub[21], add_pi[21], add_di[21];
int best_sel[21], best_sub, best_add_pi, best_add_di;

void print(int a[], int sz)
{
	int i;
	for (i=0; i<sz; i++)
		printf("%d ", a[i]);
	printf("\n");
}

void update(int sub, int add_pi, int add_di)
{
	//print();
	if ((best_sub > abs(sub)) ||
		(best_sub == abs(sub) && (best_add_pi+best_add_di) < (add_pi+add_di))) {
		best_sub = abs(sub);
		best_add_di = add_di;
		best_add_pi = add_pi;
		memcpy(best_sel, sel, sizeof(sel));
	}
}

int dfs(int next, int num)
{
	int i;
	//printf("%d %d\n", next, num);
	for (i=next; i<n; i++) {
		sel[num] = poo[i];
		sub[num] = sub[num-1] + (di[poo[i]] - pi[poo[i]]);
		add_pi[num] = add_pi[num-1] + pi[poo[i]];
		add_di[num] = add_di[num-1] + di[poo[i]];
		if (best_sub >= abs(sub[num])) {
			if (num==m)
				update(sub[num], add_pi[num], add_di[num]);
			else
				dfs(i+1, num+1);
		}
	}
	return 0;
}

int comp1(const void *a, const void *b)
{
	int ia=*(int *)a, ib=*(int *)b;
	return (pi[ib]+di[ib])-(pi[ia]+di[ia]);
	//return (pi[ia]+di[ia])-(pi[ib]+di[ib]);
}

int comp2(const void *a, const void *b)
{
	return *(int *)a-*(int *)b;
}

int main()
{
	int i, no;
	for (no=1; scanf("%d %d",&n,&m) && n>0; no++) {
		for (i=0; i<n; i++) {
			scanf("%d %d", &pi[i], &di[i]);
			sel[i] = 0; poo[i] = i+1;
		}
		qsort(poo, n, sizeof(int), comp1);
		//print(poo, n);
		sub[0] = add_pi[0] = add_di[0] = 0;
		best_sub = 20;
		best_add_pi = best_add_di = 0;
		dfs(0, 1);
		printf("Jury #%d\nBest jury has value %d for prosecution and value %d for defence:\n", no, best_add_pi, best_add_di);
		qsort(best_sel+1, m, sizeof(int), comp2);
		for (i=1; i<=m; i++)
			printf(" %d", best_sel[i]);
		printf("\n\n");
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

*/

