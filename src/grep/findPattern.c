#include "s21_grep.h"

static void Invert(char* line, char* pattern, flags* inputInfo) {
	if (inputInfo->i_ignore_case) {
		if (!strcasestr(line, pattern) && pattern) fprintf(stdout, "%s", line);
	}
	else {
		if (!strstr(line, pattern) && pattern) fprintf(stdout, "%s", line);
	}

}

static void DoNotInvert(char* line, char* pattern, flags* inputInfo) {
		if (inputInfo->i_ignore_case) {
			if (strcasestr(line, pattern) && pattern) fprintf(stdout, "%s", line);
		}
		else {
			if (strstr(line, pattern) && pattern) fprintf(stdout, "%s", line);
		}
}

static void FindPattern(char* pattern, FILE* file, flags* inputInfo) {
	ssize_t gl_return;
	size_t bufsize = 32;
	char* line = (char *)malloc(sizeof(char) * bufsize); if (!line) return exit(1);
	
	while ((gl_return = getline(&line, &bufsize, file)) != -1) {
		if (inputInfo->v_invert) Invert(line, pattern, inputInfo);
		else DoNotInvert(line, pattern, inputInfo);
	}
//	fprintf(stdout, "%s", line);
	free(line);
}

void FindAndPrintPattern(int numFiles, int* idxPatternFiles, char*** argv, flags* inputInfo) {
	char* pattern = (*argv)[idxPatternFiles[0]];
	int idx_file = 1;
	FILE* file = NULL;

	while(idx_file < numFiles) {
		s21_open_file(&file, (*argv)[idxPatternFiles[idx_file++]], "r");
		FindPattern(pattern, file, inputInfo);
		fclose(file);
	}
}
