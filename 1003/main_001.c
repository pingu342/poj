// f(n)=1/2+1/3+...+1/(n+1)
// 与えられた値cに対してf(n)>cとなる最小のnを求める

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	float c;
	int i;
	for (;i=scanf("%f", &c), c; printf("%d card(s)\n", i-1)) {
		for (; c>0 ;) c -= 1./++i;
	}
}

