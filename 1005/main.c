// 土地は毎年50平方マイルだけ半円状に侵食される
// その半円の半径(r)と年数(i)の関係は、
//    PI*r^2*0.5=50*i
//    r^2=100/PI*i
// 与えられた座標(x,y)と半円の半径(r)の関係は、
//    r^2=x^2+y^2
// 座標(x,y)が侵食されるまでの年数は、
//    x^2+y^2=100/PI*i
//    i=(x^2+y^2)/(100/PI)

#include <stdio.h>

#define PI 3.141592

int main()
{
	int i, n;
	float x, y;
	scanf("%d", &n);
	for (i=1; i<=n && scanf("%f %f", &x, &y); i++) {
		printf("Property %d: This property will begin eroding in year %d.\n",
				i, (int)((x*x+y*y)/(100./PI)+1.));
	}
	printf("END OF OUTPUT.\n");
}
