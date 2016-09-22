#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int i,n,p[16],p2,c,x;
	if (argc != 3)
		exit(1);
	sscanf(argv[1], "%d", &n);
	sscanf(argv[2], "%d", &x);
	srand(time(NULL));
	for (;;) {
		for (i=0,p2=0; i<n; i++) {
			p[i] = rand()%x+1;
			p2 += p[i]*p[i];
		}
		c = (int)sqrt(p2);
		if (c*c != p2)
			continue;
		printf("1\n%d %d ", c, n);
		for (i=0; i<n; i++)
			printf("%d ", p[i]);
		printf("\n");
		break;
	}
}
