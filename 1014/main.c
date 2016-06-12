// マーシャとビルはおはじきを集めている
// 2人は彼らのコレクションを均等に分け合いたいと考えている
// もしすべてのおはじきの価値が同じなら、ちょうど半分こすれば良いから簡単である
// しかし、他より大きかったり綺麗なおはじきがある
// そこで彼らはまず、おはじきに1から6の値で価値付けをした
// そして価値が均等になるように分け合おうとしたが、それが不可能な場合があることがわかった
// 例えば、価値1のおはじきが1つ、価値3が1つ、価値4が2つある場合は、価値が均等になるように分け合うことができない
// そこで、おはじきを均等に分け合うことができるかどうか確認するプログラムを作成せよ
//
// 入力
// 
// 価値1のおはじきが1つ、価値3が1つ、価値4が2つある場合の入力
// 1 0 1 2 0 0 
// 
// 出力
//
// Collection #1:
// Can't be divided.
//
#include <stdio.h>

int in[6];
int ccc[6];

int check(int v, int d)
{
	// 全探索バージョン
	// ぎりぎりTime Limit ExceededにならずAcceptedになった
	
	int i,m=in[v-1],n=d/v,r;
	for (i=n>m?m:n; i>=0; i--) {
		r = d-i*v;
		if (r==0) return 1; //分割できた
		if (v==1) break; //分割できなかった
		if (r>ccc[v-2]) break; //分割できなかった
		if (check(v-1, r)) return 1; //分割できた
	}
	return 0; //分割できなかった
}

int main()
{
	int n, i, s, r;
	for (n=1;scanf("%d %d %d %d %d %d", &in[0], &in[1], &in[2], &in[3], &in[4], &in[5]);n++) {
		for (i=0,s=0;i<6;i++) {
			s+=in[i]*(i+1);
			ccc[i] = s;
		}
		if (s==0) break;
		//printf("s=%d(%f)\n", s, (float)s/2.);
		if (s%2) r=0;  //奇数は均等にわけられない
		else r=check(6, s/2);
		printf("Collection #%d:\nCan%s be divided.\n\n", n, r?"":"'t");
	}
}
