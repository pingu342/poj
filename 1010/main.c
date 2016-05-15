// 顧客の希望に応じて発行する切手を在庫から選ぶ
//
// 入力：
//
// プログラムへは1回につき2行ずつ入力され、1行目が現在の切手の在庫、2行目が顧客の希望を示す
//
// 1 2 3 0	; 現在の在庫：額面が1, 2, 3の切手があり、在庫枚数に上限なし
// 7 4 0	; 顧客の希望：顧客は2人で、希望する額面はそれぞれ7、4
// 1 1 0	; 現在の在庫：額面が1の切手が2種類あり、在庫枚数に上限なし（額面は同じだが種類の異る切手が在庫にある）
// 6 2 3 0	; 顧客の希望：顧客は3人で、希望する額面はそれぞれ6、2、3
//
// 切手は最大で25種類ある
//
// 下記の条件に従い、顧客に発行する切手を在庫から選んで出力する
// ・顧客の希望する額面に正確に一致すること
// ・顧客が可能な限りたくさんの種類の切手を手に入れられること
// ・1度に発行できる切手は4枚までとすること
//
// 解が複数ある場合は下記の優先度に従う
// ・まず、切手の枚数が少ない解を優先
// ・次に、最も額面の高い切手が含まれている解を優先
//
// 上記の優先度を適用後にも複数の解が残る場合はそれらを同点として扱う
//
// 例えば、在庫が1 2 3 0で顧客の希望が5の場合、切手の種類の数が2の解が複数ある
// ・額面1を1枚と額面2を2枚（切手の枚数は3）
// ・額面1を2枚と額面3を1枚（切手の枚数は3）
// ・額面1を3枚と額面2を1枚（切手の枚数は4）
// ・額面2を1枚と額面3を1枚（切手の枚数は2）
//
// この例の場合、切手の枚数が最も少ない4番目の解を選択する
// 
// 出力：
//
// 各顧客に対して下記の値を1行で出力する
//
// ・顧客が希望する額面
// ・顧客に発行する切手の種類の数
// ・発行する切手の種類の一覧
//
// もし解が存在しない場合は、切手の種類の数に'----'、切手の種類の一覧に'none'を出力する
// もし同点の場合は、切手の種類の一覧に'tie'を出力する
//
// 7 (3): 1 1 2 3 
// 4 (2): 1 3 
// 6 ---- none 
// 2 (2): 1 1 
// 3 (2): tie 
//
// ---
// プログラムの実装例
//
// CPP
//  http://blog.csdn.net/tc_to_top/article/details/43699443
//  コンパイル
//   $ gcc sample.cpp -lstdc++
//    or
//   $ g++ sample.cpp
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STAMP_TYPES_MAX (100)
#define SELL_STAMPS_MAX (4)

int Request;
int SellStampTypesNum;
int SellStampMax;
int SellStampNum;
int Sell[SELL_STAMPS_MAX+1];
int Stock[STAMP_TYPES_MAX+1];
int Temp[SELL_STAMPS_MAX+1];
int Tie;

void debug(const char *head, int *stampTypes, int size)
{
	int i;
	printf("%s", head);
	for (i=0; i<size; i++)
		printf("%d ", stampTypes[i]);
	printf("\n");
}

void init()
{
	int i;
	SellStampTypesNum = SellStampMax = SellStampNum = 0;
	for (i=0; i<SELL_STAMPS_MAX+1; i++) { Sell[i] = 0; Temp[i] = 0; }
	Tie = 0;
}

void update(int typesNum, int stampNum, int maxStamp)
{
	SellStampTypesNum = typesNum;
	SellStampMax = maxStamp;
	SellStampNum = stampNum;
	memcpy(Sell, Temp, sizeof(int)*stampNum);
	Tie = 0;
}

void check()
{
	//debug("check: ", Temp, SELL_STAMPS_MAX+1); //debug
	int i, *p, typesNum=1, maxStamp=Temp[0]%STAMP_TYPES_MAX;
	for (i=1, p=&Temp[0]; Temp[i]; i++) {
		if (*p != Temp[i]) {
			typesNum++;
			p = &Temp[i];
		}
		if (maxStamp < (Temp[i]%STAMP_TYPES_MAX))
			maxStamp = Temp[i]%STAMP_TYPES_MAX;
	}
	if (SellStampTypesNum < typesNum)
		update(typesNum, i, maxStamp);
	else if (SellStampTypesNum == typesNum) {
		if (SellStampNum > i)
			update(typesNum, i, maxStamp);
		else if (SellStampNum == i) {
			if (SellStampMax < maxStamp)
				update(typesNum, i, maxStamp);
			else if (SellStampMax == maxStamp)
				Tie = 1;
		}
	}
}

void search(int remain, int stockNo, int tempNo)
{
	//printf("search remain:%d stockNo:%d tempNo:%d\n", remain, stockNo, tempNo); //debug
	//debug("   ", Temp, SELL_STAMPS_MAX+1);
	int stamp = Stock[stockNo]%STAMP_TYPES_MAX, i;
	if (tempNo<4 && Stock[stockNo+1])
		search(remain, stockNo+1, tempNo);
	for (i=1; i<=4-tempNo; i++) {
		if (remain < stamp*i)
			break;
		Temp[tempNo+i-1] = Stock[stockNo];
		if (remain == stamp*i) {
			Temp[tempNo+i] = 0;
			check();
			break;
		}
		if (tempNo+i<4 && Stock[stockNo+1])
			search(remain-stamp*i, stockNo+1, tempNo+i);
	}
}

static int compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int main()
{
	int i, *p;
	while (scanf("%d", &Stock[0]) != EOF) {
		for (i=0; Stock[i];)
			scanf("%d", &Stock[++i]);
		if (i==0)
			break;
		qsort(Stock, i, sizeof(int), compare);
		for (i=1, p=&Stock[0]; Stock[i]; i++)
			if (*p==Stock[i])
				Stock[i] += (STAMP_TYPES_MAX * (&Stock[i] - p));
			else
				p = &Stock[i];
		while (scanf("%d", &Request), Request) {
			init();
			search(Request, 0, 0);
			if (SellStampNum) {
				printf("%d (%d):", Request, SellStampTypesNum);
				if (Tie)
					printf(" tie");
				else
					for (i=0; i<SellStampNum; i++)
						printf(" %d", Sell[i]%STAMP_TYPES_MAX);
			} else {
				printf("%d ---- none", Request);
			}
			printf("\n");
		}
	}
}

