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
// ただしグレードは0から20であり、piとdiの両方が0である場合がありうることに注意
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

int n, m, pi[200], di[200];

//dp[a][b]
// aはmで1~20、bはD(J)-P(J)+400で0~800 ※di,piが最大20なのでdi-piは-20~20、D(J)-P(J)は-20m〜20mでmは最大20なので-400~400、+400して0~800
// 全ての要素を-1で初期化してsearch関数を実行する
// その結果、例えばm=3の場合、dp[3][400]>0だったら、D(J)-P(J)=0となるJが存在し、dp[3][400]の値はD(J)+P(J)の最大値を表す
int dp[21][801];

//sel[a][b][c]
// cはmで1~20
// 例えばm=3の場合、dp[3][400]>0だったら、sel[3][400][1~20]は、D(J)-P(J)=0でD(J)+P(J)=dp[3][400]となるJを表す
int sel[21][801][21];
/*
void print()
{
	int i, j;
	for (i=1; i<=m; i++)
		for (j=0; j<801; j++)
			if (dp[i][j])
				printf("%d,%d : %d\n", i, j-400, dp[i][j]);
	printf("\n");
}
*/
void update(int num, int sub_dp, int sum_dp, int i, int pre[])
{
	int j;
	if (dp[num][sub_dp] < sum_dp) {
		dp[num][sub_dp] = sum_dp;
		for (j=1; j<num; j++)
			sel[num][sub_dp][j] = pre[j];
		sel[num][sub_dp][j] = i;
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
				if (dp[j-1][k] != -1) {
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
		memset(dp, -1, sizeof(dp));
		memset(sel, 0, sizeof(sel));
		search();
		for (int k=0; k<=400; k++) { // |D(J)-P(J)|が0,1,2,...の順で検索
			if (dp[m][k+400] != -1 || dp[m][400-k] != -1) {
				k = (dp[m][k+400] >= dp[m][400-k]) ? k+400 : 400-k;
				//int he = dp[m][k];
				int sum_d=0, sum_p=0, sub_dp=0;
				for (l=1; l<=m; l++) {
					sum_p += pi[sel[m][k][l]-1];
					sum_d += di[sel[m][k][l]-1];
					sub_dp += di[sel[m][k][l]-1]-pi[sel[m][k][l]-1];
				}
				//if (he != sum_p+sum_d)
				//	printf("error! %d %d %d\n", he, sum_p, sum_d);
				printf("Jury #%d\nBest jury has value %d for prosecution and value %d for defence:\n", no, sum_p, sum_d);
				for (l=1; l<=m; l++)
					printf(" %d", sel[m][k][l]);
				printf("\n\n");
				break;
			}
		}
	}
}

#if 0
//全探索バージョン ちょー遅い

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n, m, pi[200], di[200], select[20];
int best_select[20], best_sub_pd, best_sum_p, best_sum_d;

void print(int a[], int sz)
{
	int i;
	for (i=0; i<sz; i++)
		printf("%d ", a[i]);
	printf("\n");
}

void update(int sub_pd, int sum_p, int sum_d)
{
	//print();
	if ((best_sub_pd > abs(sub_pd)) ||
		(best_sub_pd == abs(sub_pd) && (best_sum_p+best_sum_d) < (sum_p+sum_d))) {
		best_sub_pd = abs(sub_pd);
		best_sum_d = sum_d;
		best_sum_p = sum_p;
		memcpy(best_select, select, sizeof(select));
	}
}

void search(int num, int next, int sub_pd, int sum_p, int sum_d)
{
	if (next < n && num < m) {
		select[num] = next;
		search(num+1, next+1, sub_pd+(pi[next]-di[next]), sum_p+pi[next], sum_d+di[next]);
		search(num, next+1, sub_pd, sum_p, sum_d);
	} else if (num == m) {
		//print(select, m);
		update(sub_pd, sum_p, sum_d);
	}
}

int main()
{
	int i, no;
	for (no=1; scanf("%d %d",&n,&m) && n>0; no++) {
		for (i=0; i<n; i++) {
			scanf("%d %d", &pi[i], &di[i]);
			select[i] = 0;
		}
		best_sub_pd = 100;
		best_sum_p = best_sum_d = 0;
		search(0, 0, 0, 0, 0);
		printf("Jury #%d\nBest jury has value %d for prosecution and value %d for defence:\n", no, best_sum_p, best_sum_d);
		for (i=0; i<m; i++)
			printf(" %d", best_select[i]+1);
		printf("\n\n");
	}
}

#endif
