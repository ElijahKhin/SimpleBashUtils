#include "s21_grep.h"

static size_t DoNotIgnoreCase(char* line, char* pattern, bool invertFlag) {
	if (strstr(line, pattern)) {
		return invertFlag ? 0 : 1;
	}
	return invertFlag ? 1 : 0;
}

static size_t IgnoreCase(char* line, char* pattern, bool invertFlag) {
	if (strcasestr(line, pattern)) {
		return invertFlag ? 0 : 1;
	}
	return invertFlag ? 1 : 0;
}

static bool SearchPattern(char* line, char* pattern, flags* inputInfo) {
	if (inputInfo->i_ignore_case) 
		return IgnoreCase(line, pattern, inputInfo->v_invert);
	else 
		return DoNotIgnoreCase(line, pattern, inputInfo->v_invert);
}

static void IterLines(char* pattern, char* file_name, FILE* filep, flags* inputInfo) {
	size_t numLine = 0, matchedCnt = 0;
	size_t bufsize = 32;
	char* line = (char *)malloc(sizeof(char) * bufsize); 

	if (!line) return exit(1);
	
	while (getline(&line, &bufsize, filep) != -1) {
		numLine++;
		if (inputInfo->l_files_matched) {
			if (SearchPattern(line, pattern, inputInfo)) {
				if (inputInfo->c_count) fprintf(stdout, "%s:1\n", file_name);
				fprintf(stdout, "%s\n", file_name); 
				break;
			}
		}
//		else {
//
//		}
	}
	free(line);
}

void Grep(int numFiles, int* idxPatternFiles, char*** argv, flags* inputInfo) {
	char* pattern = (*argv)[idxPatternFiles[0]];
	int idx_file = 1;
	FILE* filep = NULL;

	while(idx_file < numFiles) {
		s21_open_file(&filep, (*argv)[idxPatternFiles[idx_file]], "r");
		IterLines(pattern, (*argv)[idxPatternFiles[idx_file++]], filep, inputInfo);
		fclose(filep);
	}
}
