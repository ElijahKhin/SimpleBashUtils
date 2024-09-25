#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* file = NULL;
	
	file = fopen("dummy.cc", "r");
	if (!file) { fprintf(stderr, "not opened"); exit(1); }
	fprintf(stdout, "opened\n");


	unsigned long rowNumber = 1;
	char c = getc(file);
	while (c != EOF) {
		if (c == '\n') fprintf(stdout, "%c%6lu\t", c, rowNumber++);
		else fprintf(stdout, "%c", c);
		c = getc(file);
	}
}
