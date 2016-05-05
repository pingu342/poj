// Haabと呼ばれるカレンダーは、1年の長さが365日、19ヶ月である
// 最初の18番目までの月は、月の長さが20日で、月の名前はpop, no, zip, zotz, tzec, xul, yoxkin, mol, chen, yax, zac, ceh, mac, kankin, muan, pax, koyab, cumhuと言う
// 最後の19番目の月は、長さが5日で、名前をuayetと言う
// 月の最初の日を0日とする
// 日付の表記は `NumberOfTheDay. Month Year` とする
//
// Tzolkinと呼ばれるカレンダーは、1年の長さが260日で、月の概念は無い
// 週に相当する概念があり、1週間の長さは13日である
// 1週間の中での位置(曜日)を1〜13の数、日を名前で表す
// 日の名前はそれぞれ、imix, ik, akbal, kan, chicchan, cimi, manik, lamat, muluk, ok, chuen, eb, ben, ix, mem, cib, caban, eznab, canac, ahauと言う
// 日付の表記は `Number NameOfTheDay Year` とする (Numberが曜日に相当)
//
// Haab、Tzolkinでは最初の年を0年とする
//
// 世界の最初の日をHaab、Tzolkinで表記するとそれぞれ以下のようになる
//   Haab    : 0. pop 0
//   Tzolkin : 1 imix 0
//
// Haabで与えられる日付をTzolkinに変換せよ

#include <stdio.h>
#include <string.h>

const char *haab[] = {"pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", "chen", "yax", "zac", "ceh", "mac", "kankin", "muan", "pax", "koyab", "cumhu", "uayet"};

const char *tzolkin[] = {"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"};

int main()
{
	int n,i,d,m,y;
	char s[8];
	scanf("%d", &n);
	printf("%d\n", n);
	for (i=0; i<n && scanf("%d. %s %d", &d, s, &y); i++) {
		for (m=0;strcmp(haab[m], s);m++) d+=20;
		d+=365*y;
		printf("%d %s %d\n", (d%(13*20))%13+1, tzolkin[(d%(13*20))%20], d/(13*20));
	}
}
