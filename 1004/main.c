// 12個の値の平均を求める

#include <stdio.h>

int main()
{
	float a, s, i;
	for (i=s=0; i<12 && scanf("%f", &a); i++) s += a;
	printf("$%g\n", s/12);
}
