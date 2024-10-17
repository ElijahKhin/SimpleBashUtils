#include "s21_grep.h"

static void FindPattern(char* pattern, FILE* file) {
	size_t bufsize = 1;
	char* line = (char *)malloc(sizeof(char) * bufsize);

	while (getline(&line, &bufsize, file) != -1) {
		if (strstr(line, pattern) && pattern) fprintf(stdout, "%s", line);
	}
}

void FindAndPrintPattern(int numFiles, int* idxPatternFiles, char*** argv, flags* inputInfo) {
	char* pattern = (*argv)[idxPatternFiles[0]];
	int idx_file = 1;
	FILE* file = NULL;

	while(idx_file <= numFiles) {
		s21_open_file(&file, (*argv)[idxPatternFiles[idx_file++]], "r");
		FindPattern(pattern, file);
		fclose(file);
	}

//	while(idx_file <= numFiles) {
//		s21_open_file(&file, (*argv)[idxPatternFiles[idx_file++]], "r");
//		FindPattern(pattern, file);
//		fclose(file);
//	}
}
