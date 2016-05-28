// ジョージは同じ長さの棒をでたらめに切りはじめた
// すべての棒の長さが最大でも50になったところで切るのをやめた
// さて、彼は棒を元に戻したい
// だが彼は、元々何本の棒があったのか、どのくらいの長さだったのか、覚えていない
// 彼を助けてください
// 切られた棒を可能な限り短い長さで元に戻すプログラムをデザインしてください
// 長さはユニットで表す
// 長さはゼロよに大きい整数とする
//
// 入力
//
// 1回の入力は2行からなる
// その1行目は切った後の棒の本数を示し、最大でも64本である
// 2行目はそれぞれの棒の長さを空白で区切ったものである
// 最後の入力は1行で0だけを含む
//
// 出力
//
// 可能な限り短い元々の棒の長さ
//
#include <stdio.h>
#include <stdlib.h>

/* [練習問題]
 * 値が5個あるとする
 * その中から値を選ぶとする
 * 値は何個選んでも良い(1個だけ選んでも、5個すべて選んでもよい)
 * その組み合わせを「再帰的な深さ優先探索(deepth-first search, DFS)」を使ってすべて列挙せよ
 */
/*
void print(int m[], int used[], int sz)
{
	int i, flag=0;
	for (i=0; i<sz; i++)
		if (used[i])
			flag = printf("%d ", m[i]);
	if (flag)
		printf("\n");
}

void dfs(int m[], int used[], int sz, int next)
{
	int i;
	for (i=next; i<sz; i++) {
		used[i] = 1;
		print(m, used, sz);
		dfs(m, used, sz, i+1);
		used[i] = 0;
	}
}

int main()
{
	int m[5] = {1,2,3,4,5}, sz=5;
	int used[5] = {0};
	dfs(m, used, sz, 0);
}
*/

/* [解答]
 */

/*
void print(int m[], int used[], int sz, int len, int n)
{
	int i, j;
	for (i=n; i<=n; i++) {
		printf("len:%d n:%d/%d use:", len, i, n);
		for (j=0; j<sz; j++) {
			if (used[j] == i)
				printf("%d(i:%d) ", m[j], j);
		}
		printf("\n");
	}
}
*/

// m[]    : 切断後の木（切れ端）それぞれの長さ
// used[] : 切れ端の探索状況
// sz     : 切れ端の本数
// n      : 「n本目」の元木を得ようと試みている
// next   : 次に試す切れ端
// len    : 元木の長さ
// remlen : 「n本目」の元木を得るには残りremlenの長さの切れ端が必要
int dfs(int m[], int used[], int sz, int n, int next, int len, int remlen)
{
	int i, nouse=0, pre=0;

	for (i=next; i<sz; i++) {
		if (!used[i]) {
			nouse++;
			if (pre != m[i]) { //前に試してダメだった切れ端と同じ長さの切れ端は試す意味がないのでショートカット
				pre = m[i];
				if (m[i] < remlen) {
					//元木を得るにはもっと切れ端が必要
					used[i] = n; //この切れ端は「n本目」の元木を得るために使用した
					if (dfs(m, used, sz, n, i+1, len, remlen-m[i]))
						return 1; //成功
					used[i] = 0;
				} else if (m[i] > remlen) {
				} else {
					//元木が得られた
					used[i] = n; //この切れ端は「n本目」の元木を得るために使用した
					if (dfs(m, used, sz, n+1, 0, len, len)) //まだ残っている切れ端を使用して「n+1本目」の元木を得る
						return 1; //成功
					used[i] = 0;
				}
			}
		}
	}

	if (next==0 && remlen==len && nouse==0) //ちょうど元木が得られた所で、切れ端の残りが0本になった
		return 1; //成功

	return 0; //失敗
}

static int compare(const void *a, const void *b)
{
	return *(int *)b - *(int *)a;
}

int main()
{
	int sz, m[64], used[64], sum, max, i;
	while (scanf("%d", &sz) != EOF && sz) {
		for (i=0,sum=0,max=0; i<sz && scanf("%d", &m[i]); i++) {
			if (m[i] > max)
				max = m[i];
			sum += m[i];
			used[i] = 0;
		}

		//長いもの順に整列させる
		qsort(m, sz, sizeof(int), compare);

		for (i=max; i<sum; i++)
			if (sum % i == 0)
				if (dfs(m, used, sz, 1, 0, i, i))
					break;
		printf("%d\n", i);
	}
}

/* テストデータ

10
1 1 1 1 1 1 1 1 1 1
3
2 3 5
5
1 9 3 5 2
10
11 7 3 1 9 5 5 9 11 7
64
1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8 1 2 3 4 5 6 7 8
5
1 1 1 1 1
2
2 3
64
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 1 2 3 4 5 6 7 8 9 10 11 12 13 14
0

1
5
10
34
8
1
5
60

*/

