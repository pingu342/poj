// サリーは1ダース(12枚)の1ドル硬貨を持っている
// しかし1枚は偽造硬貨で、その色やサイズは本物と区別がつかない
// 偽造硬貨は本物と重さが異るが、本物より軽いのか重いのかサリーにはわからない
// 幸いにもサリーには、天秤を貸してくれる友人がいる
// その友人は偽造硬貨を見つけるため3回量ることをサリーに許した
// 例えば2枚の硬貨を互いに天秤で量り、釣り合ったら2枚は本物の硬貨だ
// 次に本物の硬貨と3枚目の硬貨を互いに天秤で量り、釣り合わなかったら3枚目は偽造硬貨であり、それが本物より軽いのか重いのかがわかる
// 量る硬貨を慎重に選えば、3回量るだけで偽造硬貨を見つけられる
//
// 入力
// 
// 1 
// ABCD EFGH even 
// ABCI EFJK up 
// ABIJ EFGH even 
// 
// 最初の行はケース数(0より大きな整数n)
// 各ケースには3回量った結果が3行で入力される
// 硬貨はA-Lの英字で区別される
// 量った結果の最初の文字列は、天秤の左側の硬貨
// 2番目の文字列は、天秤の右側の硬貨
// 3番目の文字列は、天秤の右側の状態(up、down, even)
//
// 出力
//
// K is the counterfeit coin and it is light. 
//
#include <stdio.h>
#include <string.h>
/*
void print(char *c[])
{
	int i;
	for (i=0; i<12; i++) {
		printf("%c: %s\n", (i+'A'), c[i]);
	}
}
*/
char r[12], l[12], w[5]; //right, left, weigh
char *c[12]; //12coins
int n, row, found;
char *weight[]={"light","heavy"};
void update()
{
	int i, alph, side;
	for (i=0;i<12;i++) { //A-Lの硬貨12枚
		if (row==0)
			c[i] = "f"; //最初は全て偽物の可能性あり
		alph = 'A' + i;
		side = strchr(l, alph) ? 1 : strchr(r, alph) ? 2 : 0; //硬貨が天秤の左側、右側に乗っているか
		if (*w == 'e') {
			if (side) //天秤に乗っている ?
				c[i] = ""; //本物確定
		} else {
			if (side) { //天秤に乗っている ?
				if (*c[i] == 'f') //この硬貨は偽物の可能性あり ?
					c[i] = (*w=='d')?weight[side-1]:weight[(side-1)^1]; //この偽物は恐らくlight or heavy
				else if (*c[i])
					if (!(*c[i]=='l' && side==1 && *w=='d') &&
						!(*c[i]=='l' && side==2 && *w=='u') &&
						!(*c[i]=='h' && side==1 && *w=='u') &&
						!(*c[i]=='h' && side==2 && *w=='d'))
						c[i] = ""; //辻褄が合わない -> 本物確定
			} else {
				c[i] = ""; //本物確定
			}
		}
		if (*c[i]=='l' || *c[i]=='h')
			found = i; //「恐らくlight or heavyな硬貨」が残り1枚になったら偽物確定(残り1枚かどうかの確認は省略)
	}
}

int main()
{
	scanf("%d", &n);
	for (;n>0;n--) {
		for (row=0;row<3;row++) {
			scanf("%s %s %s", l, r, w);
			update();
			//print(c);
		}
		printf("%c is the counterfeit coin and it is %s.\n", 'A'+found, c[found]);
	}
}
