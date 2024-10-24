#include "s21_grep.h"

static bool GetReversedInvertFlag(bool invertFlag) {
	return invertFlag ? 0 : 1;
}

static size_t DoNotIgnoreCase(char* line, char* pattern, bool invertFlag) {
	if (strstr(line, pattern) && invertFlag) return 1;
	return 0;
}

static size_t IgnoreCase(char* line, char* pattern, bool invertFlag) {
	if (strcasestr(line, pattern) && invertFlag) return 1;
	return 0;
}

static void FindPattern(char* pattern, char* file_name, FILE* filep, flags* inputInfo) {
	size_t numLine = 0, matchedCnt = 0;
	size_t bufsize = 32;
	char* line = (char *)malloc(sizeof(char) * bufsize); 

	if (!line) return exit(1);
	
	while (getline(&line, &bufsize, filep) != -1) {
		numLine++;
		if (inputInfo->l_files_matched) {
			if (inputInfo->i_ignore_case)
				matchedCnt = IgnoreCase(line, pattern, GetReversedInvertFlag(inputInfo->v_invert));
			else {
				matchedCnt = DoNotIgnoreCase(line, pattern, GetReversedInvertFlag(inputInfo->v_invert));
			}
			if (inputInfo->c_count && matchedCnt) {
				fprintf(stdout, "%s:1\n%s\n", file_name, file_name); break;
			}
			else if (!inputInfo->c_count && matchedCnt) {
				fprintf(stdout, "%s\n", file_name); break;
			}
		}
//		else {
//
//		}
	}
	free(line);
}

void PrintMatch(int numFiles, int* idxPatternFiles, char*** argv, flags* inputInfo) {
	char* pattern = (*argv)[idxPatternFiles[0]];
	int idx_file = 1;
	FILE* filep = NULL;

	while(idx_file < numFiles) {
		s21_open_file(&filep, (*argv)[idxPatternFiles[idx_file]], "r");
		FindPattern(pattern, (*argv)[idxPatternFiles[idx_file++]], filep, inputInfo);
		fclose(filep);
	}
}
