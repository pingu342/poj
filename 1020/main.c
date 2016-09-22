// ケーキを切り分けて子供たちに食べてもらう。
// ケーキは正方形で、子供たちが食べるケーキも正方形とする。
// 子供たちに食べたいケーキの大きさを聞き、ケーキが余らないかどうかを知りたい。
//
// 入力
//
// 最初の行はテストケース数t(ただし1<=t<=10)で、その後にテストケースの行が続く。
// 各テストケースは1行で、最初にケーキの大きさ(正方形の辺の長さ)、
// その次にケーキを食べる子供の人数n(ただし1<=n<=16)、
// その次に子供たちが食べたいケーキの大きさ(正方形の辺の長さ1〜10)のリスト。
//
// 出力
// 
// 無駄が出ないならKHOOOOB!
// 無駄が出るならHUTUTU!
//
// 考え方
//
// 子供が食べるケーキの最大は10x10
// 子供の人数は最大で16
// なのでケーキの最大面積は16*10*10で、その辺の長さは40
//
// 問題を言い換えると、大きさが最大40x40の碁盤と、大きさが1x1〜10x10の石がn個あって、
// その石を全て使って碁盤を綺麗に埋められるかどうか、という問題。
//
// すぐ思いつく解き方は、とにかく石をマスに置いてみて、だめだったら石を置く位置を前と変えてみて、それでもだめならまた位置を変えてみて、全てのパターンを試験すること。
// 例えば、40x40の碁盤に、1x1の石を置く場合、置く位置は1600通りある。
// その次に1x1の石を置く場合、置く位置は1599通りある。
// 全ての組み合わせを試せば答えが得られるが、組み合わせの数が膨大だ。
//
// この問題はゲームのテトリスに置き換えられる。
// 最大40x40のマスに、1x1〜10x10のブロックが上から順に落ちてくる。
// 歯抜けが出ないようにうまくブロックを積めるかという問題。
//
// 問題を解くには、落ちてきたブロックを積む位置を決めるアルゴリズムが必要である。
// アルゴリズムを単純化するため、綺麗に積まれていない最下段の一番左に必ず置く、という制限を設ける。
// 例えば3x3のマスに、1x1のブロックが連続で落ちてきた場合は左から順においていく。
// 右から順に置いたり、2個目のブロックを1個目の上に重ねて置いたりはできない。
// この制限下でブロックを置けない場合は、ブロックを落す順序を変えて最初からやり直す。
// 例えば3x3のマスに、1x1のブロック2個の後に2x2のブロックが落ちてきたら置けないが、落す順序を変えれば置くことができる。
// またブロックは最大16個、大きさ10種類なので、同じ大きさのブロックが存在する。
// なので例えば1個目に落すブロックは最大16通りではなく、最大10通りを調べれば良い。
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// とにかく石をマスに置いてみて、だめだったら石を置く位置を前と変えてみて、それでもだめならまた位置を変えてみて、、、を繰り返して解く
/*
int t,c,n,p[16],c2;
int cake[40*40];

int compare(const void *a, const void *b)
{
	return *(int *)b - *(int *)a;
}

int test(int x, int y, int l)
{
	int i,j;
	for (i=0; i<l; i++)
		for (j=0; j<l; j++)
			if (cake[(y+j)*c+(x+i)])
				return 0; //NG
	for (i=0; i<l; i++)
		for (j=0; j<l; j++)
			cake[(y+j)*c+(x+i)] = 1;
	return 1; //OK
}

void clear(int x, int y, int l)
{
	int i,j;
	for (i=0; i<l; i++)
		for (j=0; j<l; j++)
			cake[(y+j)*c+(x+i)] = 0;
}

int dfs(int next)
{
	int x,y,l;
	if (next == n)
		return 1; //OK
	l = p[next];
	if (c2 < l*l)
		return 0; //NG
	for (x=0; x<=c-l; x++)
		for (y=0; y<=c-l; y++)
			if (test(x, y, l)) {
				c2 -= l*l;
				if (dfs(next+1))
					return 1; //OK
				clear(x, y, l);
				c2 += l*l;
			}
	return 0; //NG
}

int main()
{
	int i,p2;
	for (scanf("%d", &t); t; t--) { //テストケース
		scanf("%d", &c); //ケーキの大きさ
		c2 = c*c; //ケーキの面積
		for (scanf("%d", &i),n=p2=0; n<i; n++) { //人数
			scanf("%d", &p[n]);
			p2 += p[n]*p[n]; //子供が食べるケーキの面積の合計
		}
		printf("c2=%d p2=%d\n", c2, p2);
		qsort(p, n, sizeof(int), compare); //降順ソート
		memset(cake, 0, sizeof(int)*c2);
		if (c2==p2 && dfs(0))
			printf("KHOOOOB!\n");
		else
			printf("HUTUTU!\n");
	}
}
*/

//テトリスの考え方で解く

int t,c,n,p[10+1],c2;
int cake[40]; //積んだブロックの高さ

int compare(const void *a, const void *b)
{
	return *(int *)b - *(int *)a;
}

int dfs(int next)
{
	int i,j,min,len;
	if (next == n)
		return 1; //OK
	for (i=1,min=0,len=1; i<c; i++) {
		if (cake[i] < cake[min]) {
			min = i; //積んだブロックの高さが最も低い場所
			len = 1; //低い場所が連続する長さ
		} else if (i==min+len && cake[i]==cake[min]) {
			len++;
		}
	}
	for (i=10; i>0; i--) {
		if (p[i]>0 && i<=len && i<=c-cake[min]) {
			for (j=0; j<i; j++)
				cake[min+j] += i;
			p[i]--;
			if (dfs(next+1))
				return 1; //OK
			for (j=0; j<i; j++)
				cake[min+j] -= i;
			p[i]++;
		}
	}
	return 0; //NG
}

int main()
{
	int i,j,p2;
	for (scanf("%d", &t); t; t--) { //テストケース
		memset(cake, 0, sizeof(cake));
		memset(p, 0, sizeof(p));
		scanf("%d", &c); //ケーキの大きさ
		c2 = c*c; //ケーキの面積
		for (scanf("%d", &i),n=p2=0; n<i; n++) { //子供の人数
			scanf("%d", &j); //子供が食べるケーキの大きさ
			p2 += j*j; //子供が食べるケーキの面積の合計
			p[j]++;
		}
		if (c2==p2 && dfs(0))
			printf("KHOOOOB!\n");
		else
			printf("HUTUTU!\n");
	}
}

/*
テストケース
1
24 16 2 4 4 10 1 5 8 5 2 9 1 9 9 2 8 3
*/
