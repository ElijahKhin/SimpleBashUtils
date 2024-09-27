#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* file = fopen("nonPrintingChars", "w"); if (!file) return 1;
	for (int i = 0; i < 33; i++) fprintf(file, "%d: %c\n", i, i);
}
