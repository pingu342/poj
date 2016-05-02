#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long NUMBER;

static char buf[64];
static NUMBER *numbers;
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

static int compare(const void *a, const void *b)
{
	return *(NUMBER *)a - *(NUMBER *)b;
}

int main() {
	int i, max;
	scanf("%d", &max);
	numbers = malloc(sizeof(NUMBER)*(max+1));
	memset(numbers, 0, sizeof(NUMBER)*(max+1));
	for (i=0; i<max; i++) {
		scanf("%s", buf);
		numbers[i] = parse(buf);
	}
	qsort(numbers, max, sizeof(NUMBER), compare);
	int duplicates=0;
	for (i=0; i<max; i++) {
		NUMBER n = numbers[i];
		int j = i + 1;
		while (n==numbers[j] && j<max) {
			j++;
		}
		if ((j - i) > 1) {
			printf("%03d-%04d %d\n", (int)n/10000, (int)n%10000, (j - i));
			duplicates = 1;
			i = j - 1;
		}
	}
	if (!duplicates) {
		printf("No duplicates.\n");
	}
	free(numbers);
}
