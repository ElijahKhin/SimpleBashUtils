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

static bool SearchPattern(char* line, char* pattern, flags* flagsInfo) {
	if (flagsInfo->i_ignore_case) 
		return IgnoreCase(line, pattern, flagsInfo->v_invert);
	else 
		return DoNotIgnoreCase(line, pattern, flagsInfo->v_invert);
}

static void PrintResult(int outputCode, char* line, char* pattern, char* file_name, size_t numLine) {
	if (outputCode == 1) fprintf(stdout, "%s:1\n%s\n", file_name, file_name);
	else if (outputCode == 2) fprintf(stdout, "1\n%s\n", file_name);
	else if (outputCode == 3) fprintf(stdout, "%s\n", file_name);
	else if (outputCode == 4) fprintf(stdout, "%s", line);
	else if (outputCode == 5) fprintf(stdout, "%s\n", pattern);
	else if (outputCode == 6) fprintf(stdout, "%zu:%s", numLine, line);
	else if (outputCode == 7) fprintf(stdout, "%zu:%s\n",numLine, pattern);
	else if (outputCode == 8) fprintf(stdout, "%s:%s", file_name, line);
	else if (outputCode == 9) fprintf(stdout, "%s", line);
	else if (outputCode == 10) fprintf(stdout, "%s:%s\n", file_name, pattern);
	else if (outputCode == 11) fprintf(stdout, "%s\n", pattern);
	else if (outputCode == 12) 
		fprintf(stdout, "%s:%zu:%s", file_name, numLine, line);
	else if (outputCode == 13) fprintf(stdout, "%zu:%s", numLine, line);
	else if (outputCode == 14) 
		fprintf(stdout, "%s:%zu:%s\n", file_name, numLine, pattern);
	else if (outputCode == 15) fprintf(stdout, "%zu:%s\n", numLine, pattern);
	else fprintf(stdout, "other codes");
}

static int ShortWay(int numFiles, flags* flagsInfo) {
	if (flagsInfo->c_count) {
		if (numFiles != 1) 
			return 1;
		else 
			return 2;
	}
	return 3;
}

static int LW_NoCountWithFileName(flags* flagsInfo) {
	if (!flagsInfo->n_line_number) {
		if (!flagsInfo->o_only_matching) return 4;
		else return 5;
	}
	else {
		if (!flagsInfo->o_only_matching) return 6;
		else return 7;
	}
}

static int LW_NoCountNoFileName(int numFiles, flags* flagsInfo) {
	if (!flagsInfo->n_line_number) {
		if (!flagsInfo->o_only_matching) {
			if (numFiles!=1) return 8;
			else return 9;
		}
		else {
			if (numFiles!=1) return 10;
			else return 11;
		}
	}
	else {
		if (!flagsInfo->o_only_matching) {
			if (numFiles!=1) return 12;
			else return 13;
		}
		else {
			if (numFiles!=1) return 14;
			else return 15;
		}
	}
}

static int LW_DoNotCount(int numFiles, flags* flagsInfo) {
	if (!flagsInfo->h_no_file_name) {
		return LW_NoCountNoFileName(numFiles, flagsInfo);
	}
	else {
		return LW_NoCountWithFileName(flagsInfo);
	}
}

static int LongWay(size_t* numMatched, int numFiles, flags* flagsInfo) {
	if (!flagsInfo->c_count) {
		return LW_DoNotCount(numFiles, flagsInfo);
	}
	else {
		(*numMatched)++;
		return 0;
	}
}

static void GetOutputCode(char* pattern, FILE* filep, char* file_name, int numFiles, flags* flagsInfo) {
	int outputCode = 0; 
	size_t numMatched = 0, numLine = 0;
	size_t bufsize = 32;
	char* line = (char *)malloc(sizeof(char) * bufsize); 

	if (!line) return exit(1);
	while (getline(&line, &bufsize, filep) != -1) {
		numLine++;
		if (flagsInfo->l_files_matched) {
			if (SearchPattern(line, pattern, flagsInfo)) {
				outputCode = ShortWay(numFiles, flagsInfo);
			}
		}
		else {
			if (SearchPattern(line, pattern, flagsInfo)) {
				outputCode = LongWay(&numMatched, numFiles, flagsInfo);
			}
		}
		if (outputCode) {
			PrintResult(outputCode, line, pattern, file_name, numLine);
			if (outputCode < 4) break;
		}
		outputCode = 0;
	}
//	if (numMatched) {
//	}
}

void Grep(char*** argv, flags* flagsInfo, files* filesInfo) {
	int idx_file = 0;
	FILE *filep = NULL;
	char *file_name, *pattern = (*argv)[filesInfo->idxPatternFiles[0]];
	
	while(++idx_file <= filesInfo->numFiles) {
		file_name = (*argv)[filesInfo->idxPatternFiles[idx_file]];
		s21_open_file(&filep, file_name, "r");
		GetOutputCode(pattern, filep, file_name, filesInfo->numFiles, flagsInfo);
		fclose(filep);
	}
}
