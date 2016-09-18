// 特別な通信システムの注文を受けた
// システムは幾つかのデバイスで構成から成る
// デバイスのメーカーは自由に選べる
// 同じデバイスでもメーカーが異なると帯域や価格が違う
// 選んだデバイスの帯域の最低値を全体帯域(B)、選んだデバイスの価格の合計を総価格(P)として、
// B/Pが最大になるように各デバイスを選ぶ
//
// 入力
//
// まず最初の行はテストケースの個数t(ただし1<=t<=10)を含む
// 次に各テストケースの行が続く
// 各テストケースは、システムのデバイス数n(ただし1<=n<=100)を含む行で始まり、その後に以下のフォーマットの行がn個だけ続く
// i番目(ただし1<=i<=n)の行は、i番目のデバイスのメーカーの数mi(ただし1<=mi<=100)で始まり、その後に各メーカーのデバイスの帯域と価格のペアがmi個だけ続く
// 
// 出力
//
// 各テストケースについて、B/Pの最大値を含んだ1行を出力すること
// 小数点以下3桁に四捨五入すること
//

#include <stdio.h>
#include <stdlib.h>

/*
// 深さ優先探索version (計算量多い)

int t, n, mi[100];
struct mf {int bw; int pr;} m[100][100];
int B, P;
float max;

//void print()
//{
//	int i,j;
//	for (i=0; i<n; i++)
//		for (j=0; j<mi[i]; j++)
//			printf(" [%02d-%02d] %d %d\n", i, j, m[i][j].bw, m[i][j].pr);
//}

void dfs(int d, int b, int p)
{
	int i;
	if (d==n) {
		if (max < (float)b/p) {
			max = (float)b/p;
			B = b;
			P = p;
		}
		return;
	}
	if (B >= b && P <= p) {
		return;
	}
	for (i=0; i<mi[d]; i++) {
		if (b > m[d][i].bw)
			dfs(d+1, m[d][i].bw, p+m[d][i].pr);
		else
			dfs(d+1, b, p+m[d][i].pr);
	}
}

//int compare_pr(const void *a, const void *b)
//{
//	const struct mf *ma=a, *mb=b;
//	return ma->pr - mb->pr;
//} 
//
//int compare_bw(const void *a, const void *b)
//{
//	const struct mf *ma=a, *mb=b;
//	return mb->bw - ma->bw;
//}

int main()
{
	int i,j;
	scanf("%d", &t);
	for (;t;t--) {
		scanf("%d", &n);
		for (i=0; i<n; i++) {
			scanf("%d", &mi[i]);
			for (j=0; j<mi[i]; j++)
				scanf("%d %d", &m[i][j].bw, &m[i][j].pr);
//			qsort(m[i], mi[i], sizeof(struct mf), compare_pr); //価格の昇順でソート
//			qsort(m[i], mi[i], sizeof(struct mf), compare_bw); //帯域の降順でソート
		}
//		print();
		max = 0.;
		B = P = 0;
		dfs(0, (1<<(sizeof(int)*8-1))-1, 0);
		printf("%.3f\n", max); //四捨五入して小数点以下3桁に丸める
	}
}
*/

// DP version

#define MAX_BW (2000)
#define MIN(a,b) ((a)<(b)?(a):(b))

int dp[100][MAX_BW];

int main()
{
	int i,j,k,t,n,m,b,p,inf=1000000;
	float ans,bpp;
	scanf("%d", &t); //テストケース数
	for (;t;t--) {
		scanf("%d", &n); //デバイス数
		for (i=0; i<100; i++) //DP初期化
			for (j=0; j<MAX_BW; j++)
				dp[i][j] = inf;
		for (i=0; i<n; i++) {
			scanf("%d", &m); //メーカー数
			for (j=0; j<m; j++) {
				scanf("%d %d", &b, &p); //帯域, 価格
				if (i==0) {
					dp[0][b] = p;
				} else {
					for (k=0; k<MAX_BW; k++) {
						if (dp[i-1][k] != inf) {
							if (k < b)
								dp[i][k] = MIN(dp[i][k],dp[i-1][k]+p);
							else
								dp[i][b] = MIN(dp[i][b],dp[i-1][k]+p);
						}
					}
				}
			}
		}
		for (i=0,ans=0.; i<MAX_BW; i++) {
			if (dp[n-1][i] != inf) {
				bpp = (float)i/dp[n-1][i];
				if (bpp > ans)
					ans = bpp;
			}
		}
		printf("%.3f\n", ans); //四捨五入して小数点以下3桁に丸める
	}
}
