#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long NUMBER;

static char buf[64];
static NUMBER *numbers;
static NUMBER *uppers;
static const char letter[] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,0,7,7,8,8,8,9,9,9,0};

static long parse(char *buf)
{
	long number;
	char *p = buf;
	char c;
	int n, k=1000000;
	while ((c=*(p++)) != '\0') {
		if (0x30<=c && c<=0x39) { //0-9
			n = c - 0x30;
		} else if (0x41<=c && c<=0x60) { //A-Z
			n = letter[c - 'A'];
			if (n == 0) continue;
		} else {
			continue;
		}
		number += (n * k);
		if (k == 1) break;
		k /= 10;
	}
	return number;
}

int main() {
	int i, j;
	scanf("%d", &i);
	numbers = malloc(sizeof(NUMBER)*10000000);
	memset(numbers, 0, sizeof(NUMBER)*10000000);
	uppers = malloc(sizeof(NUMBER)*1000);
	memset(uppers, 0, sizeof(NUMBER)*1000);
	while (i > 0) {
		scanf("%s", buf);
		long n = parse(buf);
		numbers[n]++;
		uppers[n/10000]++;
		i--;
	}
	int duplicates=0;
	for (i=0; i<1000; i++) {
		if (uppers[i] > 0) {
			for (j=0; j<10000; j++) {
				long n = i*10000 + j;
				if (numbers[n] >= 2) {
					printf("%03d-%04d %d\n", i, j, (int)numbers[n]);
					duplicates = 1;
				}
			}
		}
	}
	if (!duplicates) {
		printf("No duplicates.\n");
	}
	free(numbers);
	free(uppers);
}
