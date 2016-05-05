// A,C,G,Tの文字から成る文字列の配列を、文字列のsortednssが大きい順に並べ替える
// 例えば文字列'DAABEC'のsortednssは、Dが右の4文字(A,A,B,C)より大きく、Eが右の1文字(C)より大きいので、それらを合計した5とする

#include <stdio.h>
#include <stdlib.h>

typedef struct { short a; char b[1]; } E;

static int compare(const void *a, const void *b)
{
	return ((E*)a)->a - ((E*)b)->a;
}

int main()
{
	E* e;
	int n,m,s,i,j,k;
	char *l;
	scanf("%d %d", &n, &m);
	s = n+1+sizeof(short)*2;
	s -= s%sizeof(short);
	l = malloc(s*m);
	for (i=0;i<m;i++) {
		e = (E*)(l+s*i);
		scanf("%s", e->b);
		for (e->a=0,j=n-1;j>0;j--)
			for (k=0;k<j;k++)
				if (e->b[j]<e->b[k])
					e->a++;
	}
	qsort(l, m, s, compare);
	for (i=0;i<m;i++) {
		e = (E*)(l+s*i);
		printf("%s\n", e->b);
	}
}
