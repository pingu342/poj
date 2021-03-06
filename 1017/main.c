// 工場で製造された製品をコンテナに詰めて輸送する。
// 製品の高さはすべてhで、幅と奥行きは1*1,2*2,3*3,4*4,5*5,6*6の種類がある。
// コンテナの高さは製品と同じhで、幅と奥行きは6*6である。
// 輸送コストを抑制するには、コンテナに製品を効率よく詰めて、コンテナ数を少なくする必要がある。
// 与えられた製品の個数に対するコンテナ数を出力するプログラムを作れ。
//
// * * * * * *
// * * * * * *
// * * * * * *
// * * * * * *
// * * * * * *
// * * * * * *
//
// 入力
// 0 0 4 0 0 1 
// 7 5 1 0 0 0 
// 0 0 0 0 0 0 
//
// 出力
// 2
// 1
//

#include <stdio.h>

int n, p[6];

int pk(int i, int n) //pack
{
	int a = p[i] - n;
	p[i] = a<0 ? 0 : a;
	return a<0 ? -1*a : 0;
}

//void print()
//{
//	int i;
//	for (i=0; i<6; i++)
//		printf("%d ", p[i]);
//	printf("\n");
//}

int main()
{
	int i, s, a;
	for (;;) {
		for (i=0,s=0;i<6&&scanf("%d",&p[i]);i++) s+=p[i];
		if (s==0) break;
		//6*6
		n = p[5]; //6*6の数だけコンテナが必要、マス余りなし
		//5*5
		n += p[4]; //5*5の数だけコンテナが必要
		pk(0, 11*p[4]); //1コンテナあたり、1*1のマスが11余るので、そこに1*1を詰める
		//4*4
		n += p[3]; //4*4の数だけコンテナが必要
		pk(0, pk(1, 5*p[3])*4); //1コンテナあたり、2*2のマスが5余るので、そこに2*2を詰めて、その後に余ったマスに1*1を詰める
		//3*3
		a = p[2] % 4;
		n += p[2]/4+(a?1:0); //3*3は1コンテナに4つ詰められる
		if (a==3)
			pk(0, pk(1, 1)*4+5); //2*2のマスが1と1*1のマスが5余るので、そこに2*2を詰めて、その後に余ったマスに1*1を詰める
		else if (a==2)
			pk(0, pk(1, 3)*4+6); //2*2のマスが3と1*1のマスが6余るので、そこに2*2を詰めて、その後に余ったマスに1*1を詰める
		else if (a==1)
			pk(0, pk(1, 5)*4+7); //2*2のマスが5と1*1のマスが7余るので、そこに2*2を詰めて、その後に余ったマスに1*1を詰める
		//2*2
		a = p[1] % 9;
		n += p[1]/9+(a?1:0); //2*2は1コンテナに9つ詰められる
		if (a > 0)
			pk(0, (9-a)*4); //余ったマスに1*1を詰める
		//1*1
		n += p[0]/36+((p[0]%36)?1:0); //1*1は1コンテナに36つ詰められる
		printf("%d\n", n);
	}
	printf("\n");
}

