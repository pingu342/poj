#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// テストデータ作成
int main()
{
	int i, n, m, r=10000;
	srand(time(NULL));
	while (r--) {
		n = (rand()%200)+1; //1<=n<=200
		m = (rand()%(n>=20?20:n))+1; //1<=m<=20
		printf("%d %d\n", n, m);
		while (n--)
			printf("%d %d\n", rand()%21, rand()%21);
		if (r)
			printf("\n");
	}
	printf("0 0\n");
}
