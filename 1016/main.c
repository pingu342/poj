// クロネッカーのKナンバーは、看板に使うプラスチックの数字を作る小さな会社です。
// オーナー兼従業員であるクライド・クロネッカーは、注文された数字の個数を管理簿に記録しています。
// 例えば、"5553141" という数が注文された場合、"5553141" の一行を記録します。
// その次の行に、各数字の個数（1が2つ、3が1つ、４が1つ、5が3つ) を、"21131435" のように凝縮した形で記録します。
// ここで、"21131435" を、注文された数 "5553141" のインベントリと言い、"5553141" を "21131435" に変換する関数をインベントリ関数と言います。
// 先日彼は、"31123314" という数の注文を受けた時、この数のインベントリ(1が3つ、2が1つ、3が3つ、4が1つなので31123314)が、注文された数と同じことに気づいて驚きました。
// 
// 注文された数をnとします。
// nは非負の整数です。
// nをインベントリ関数に入力したときの出力を、nのインベントリと呼びます。
// nのインベントリがnと一致する場合を、"n is self-inventorying" と言います。
// また、nのインベントリを更に在庫関数に入力して、その出力を更に入力して、、、というループをj回(j>=1)繰り返したとき(j=0はnを入力とする最初のインベントリ関数、j=1はその出力を入力とする次のインベントリ関数、以降j=2,3,...)、在庫関数の入力と出力が一致する場合を、"n is self-inventorying after j steps" と言います。なおj=0で一致する場合は"n is self-inventorying"に該当します。
// また、j回目の在庫関数の出力がj+k回目(k>=2)の出力と一致する場合を、"n enters an inventory loop of length k" と言います。なおk=1、すなわちj回目の在庫関数の出力がj+1回目の出力と一致する場合は"n is self-inventorying after j steps"に該当します。
// また、j=14の在庫関数で、上記のどれにも当てはまらない場合を、"n can not be classified after 15 iterations" と言います。

#include <stdio.h>
#include <string.h>

void f(char *out, char *in)
{
	int i, c[10];
	memset(c, 0, sizeof(c));
	for (;*in;in++)
		c[*in-'0']++;
	for (i=0; i<10; i++)
		if (c[i])
			out += sprintf(out, "%d%d", c[i], i);
}

int main()
{
	int j, k;
	char n[17][81]; //80 digits + '¥0'
	while (scanf("%s", n[0]) && strcmp(n[0], "-1")!=0) {
		f(n[1], n[0]);
//		printf("j=0: %s -> %s\n", n[0], n[1]);
		if (strcmp(n[1], n[0]) == 0) {
			printf("%s is self-inventorying\n", n[0]);
		} else {
			for (j=1; j<15; j++) {
				f(n[j+1], n[j]);
//				printf("j=%d: %s -> %s\n", j, n[j], n[j+1]);
				for (k=1; k<=j; k++)
					if (strcmp(n[j+1], n[j-k+1]) == 0)
						goto output;
			}
output:
			if (j<15 && k==1)
				printf("%s is self-inventorying after %d steps\n", n[0], j);
			else if (j<15 && k>=2)
				printf("%s enters an inventory loop of length %d\n", n[0], k);
			else
				printf("%s can not be classified after 15 iterations\n", n[0]);
		}
	}
}
