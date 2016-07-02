#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// テストデータ作成
int main(int argc, char *argv[])
{
	int opt, _n, _m;
	int i, n=0, m=0, r=1, s=0;
	while ((opt = getopt(argc, argv, "n:m:r:s:")) != -1) {
		if (opt == 'n')
			sscanf(optarg, "%d", &_n);
		else if (opt == 'm')
			sscanf(optarg, "%d", &_m);
		else if (opt == 'r')
			sscanf(optarg, "%d", &r);
		else if (opt == 's')
			sscanf(optarg, "%d", &s);
	}
	if (_n==0 || _m==0)
		return 0;
	if (s==0)
		srand(time(NULL));
	else
		srand(s);
	while (r--) {
//		n = (rand()%200)+1; //1<=n<=200
//		m = (rand()%(n>=20?20:n))+1; //1<=m<=20
		n = _n;
		m = _m;
		printf("%d %d\n", n, m);
		while (n--)
			printf("%d %d\n", rand()%21, rand()%21);
		if (r)
			printf("\n");
	}
	printf("0 0\n");
}
