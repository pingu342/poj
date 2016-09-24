/*
 w * hサイズの碁盤にn個の石が置かれている
 プレーヤーは交互に石を取る
 最後の石を取った人が勝ち
 行や列で連続している石は1度にまとめて取れる
 例えば以下の例では、aだけ取る、aとbを取る、aとdを取ることができる
 aとeを取ることはできない

 a b - - c 
 d e - - f 
 - - - - - 

 3 3     2 
 3 3     2 

 以下の例は、上の例と石の配置が違うが本質的には同等で、同じ戦略を適用できる

 a - b c - 
 d - e f - 
 - - - - - 

 2   3 3   
 2   3 3   

 2つの碁盤の状態が、上のように同等かどうかを判定したい

 連続する石の集団が、上下左右に反転、回転、移動しているだけなら同等
 例えば以下の2つの例は同等

 a - b - - 
 d - e c - 
 - - - f - 

 2   2     
 2   3 3   
       2   

 a b - - - 
 - - c d - 
 - - - e f 

 2 2       
     2 3   
       3 2 

 以下の2つの例は同等でない

 a - b - - 
 d - e c - 
 - - - f - 

 2   2     
 2   3 3   
       2   

 a b - - - 
 - - - c - 
 - - d e f 

 2 2       
       2   
     3 4 3 

 以下の2つの例も同等でない

 a - b - - 
 d - e c - 
 - - - f - 

 2   2     
 2   3 3   
       2   

 a b - - - 
 c - - - d 
 - - - e f 

 3 2       
 2       2 
       2 3 

 以下の2つの例も同等でない (と思うのだが、下のプログラムでは同等と判断してしまう... でもAcceptされたので同等が正しい判断なのか...?)

 a b - - - 
 c - - - - 
 d - - - - 

 4 2
 3
 3

 a - - - - 
 c b - - - 
 d - - - - 

 3
 4 2
 3

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAP(i,x,y) (map[(i)][(x)+(y)*w])

int t,w,h,n;
int map[2][102*102];

int compare(const void *a, const void *b)
{
	return *(int *)b - *(int *)a;
}
/*
void print(int i)
{
	int x,y;
	printf("\n");
	for (y=1; y<=h; y++) {
		for (x=1; x<=w; x++) {
			printf("%d ", MAP(i, x, y));
		}
		printf("\n");
	}
}

void print2()
{
	int i,j;
	printf("\n");
	for (i=0; i<2; i++) {
		for (j=0; j<102*102 && map[i][j]>0; j++) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}
*/
int main()
{
	int i,j,x,y;
	for (scanf("%d", &t); t; t--) {
		memset(map, 0, sizeof(map));
		scanf("%d %d %d", &w, &h, &n);
		for (i=0; i<2; i++)
			for (j=0; j<n; j++) {
				scanf("%d %d", &x, &y);
				MAP(i, x+1, y+1) = 1;
			}
		for (i=0; i<2; i++) {
//			print(i);
			for (x=1; x<=w; x++) {
				for (y=1; y<=h; y++) {
					if (MAP(i, x, y)) {
						for (j=x+1; j<=w && MAP(i,j,y); j++) MAP(i,x,y)++;
						for (j=x-1; j>=1 && MAP(i,j,y); j--) MAP(i,x,y)++;
						for (j=y+1; j<=h && MAP(i,x,j); j++) MAP(i,x,y)++;
						for (j=y-1; j>=1 && MAP(i,x,j); j--) MAP(i,x,y)++;
					}
				}
			}
//			print(i);
			qsort(map[i], 102*102, sizeof(int), compare);
		}
//		print2();
		if (memcmp(map[0], map[1], sizeof(int)*102*102) == 0)
			printf("YES\n");
		else
			printf("NO\n");
	}
}
