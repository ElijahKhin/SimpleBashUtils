#include <stdio.h>
#include <stdlib.h>

int main() {
	char min_int[11] = "-2147483648";
	char *itoa;

	itoa = malloc(12);
	int i = 0;
	while(min_int[i]) {
		itoa[i] = min_int[i];
		i++;
	}

//	printf("%s\n", min_int);
	printf("%s", itoa);
}
