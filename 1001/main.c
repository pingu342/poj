#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (100)
#define ASSERT(x) { if (!(x)) { printf("%d: assert error.\n", __LINE__); abort(); } }

typedef struct {
	long mantissa[MAX]; //mantissa[0]:仮数部の1の位, mantissa[1]:仮数部の2の位, ...
	long exponent;
} BigNum;

static void parse(BigNum *bigNum, char *buf)
{
	int i=0, n;
	long leadingZero=1;
	char *p = strchr(buf, '\0');
	p--;
	bigNum->exponent = 0;
	while (i<MAX) {
		if (*p == '.') {
			p--;
			break;
		} else if (leadingZero && *p == '0') {
			//skip
		} else {
			n = *p - 0x30;
			bigNum->mantissa[i++] = n;
			bigNum->exponent--;
			leadingZero = 0;
		}
		p--;
	}
	while (i<MAX) {
		n = *p - 0x30;
		bigNum->mantissa[i++] = n;
		if (p == buf) {
			break;
		}
		p--;
	}
	while (i<MAX) {
		bigNum->mantissa[i++] = 0;
	}
}

static void mul(BigNum *a, BigNum *b)
{
	BigNum origin_a;
	long tmp;
	int i, j;
	memcpy(&origin_a, a, sizeof(BigNum));
	parse(a, "0.0");
	for (i=0; i<MAX; i++) {
		for (j=0; j<MAX; j++) {
			tmp = a->mantissa[i+j];
			tmp += b->mantissa[i] * origin_a.mantissa[j];
			a->mantissa[i+j] = (tmp % 10);
			a->mantissa[i+j+1] += (tmp / 10);
		}
	}
	a->exponent = origin_a.exponent + b->exponent;
}

static char *toString(char *buf, BigNum *bigNum)
{
	char *p = buf;
	int i, j, n, exponent;
	for (i=MAX-1; i>=0; i--) {
		if (bigNum->mantissa[i] != 0) {
			break;
		}
	}
	exponent = bigNum->exponent + i + 1;
	if (exponent <= 0) {
		//*(p++) = '0';
		*(p++) = '.';
		for (; exponent<0; exponent++) {
			*(p++) = '0';
		}
	}
	for (j=0; i>=0; i--) {
		if (exponent > 0 && j == exponent) {
			*(p++) = '.';
		}
		j++;
		n = bigNum->mantissa[i];
		ASSERT(0 <= n && n <= 9);
		*(p++) = (n + 0x30);
	}
	*p = '\0';
	return buf;
}

int main() {
	static char buf[256];
	char *tmp;
	int n;
	BigNum r, z;
	while(scanf("%s%d", buf, &n) == 2) {
		parse(&r, buf);
		parse(&z, "1.0");
		while (n) {
			mul(&z, &r);
			n--;
		}
		printf("%s\n", toString(buf, &z));
	}
}
