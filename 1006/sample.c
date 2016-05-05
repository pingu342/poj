#include <stdio.h>

#define C_PHY 23
#define C_EMO 28
#define C_INT 33

int findpeak(int a, int ca, int b, int cb)
{
    a -= b;
    while (a % cb != 0) {
        a += ca;
    }
    return a+b;
}

int main()
{
    int n;
    for (n = 1; ; n++) {
        int p, e, i, d;
        scanf("%d %d %d %d", &p, &e, &i, &d);
        if (p == -1) break;

        int tmp;
        tmp = findpeak(e, C_EMO, i, C_INT);
        tmp = findpeak(tmp, C_EMO*C_INT, p, C_PHY);

        tmp -= d;
        if (tmp <= 0) tmp += C_EMO*C_INT*C_PHY;
        else if (tmp > C_EMO*C_INT*C_PHY) tmp -= C_EMO*C_INT*C_PHY;

        printf("Case %d: the next triple peak occurs in %d days.\n", n, tmp);
    }
    return 0;
}
