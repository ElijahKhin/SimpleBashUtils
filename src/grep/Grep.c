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

static void GetOutputCode(char* pattern, FILE* filep, char* file_name, int numFiles, flags* flagsInfo) {
	size_t numMatched = 0, numLine = 0;
	size_t bufsize = 32;
	char* line = (char *)malloc(sizeof(char) * bufsize); 

	if (!line) return exit(1);
	while (getline(&line, &bufsize, filep) != -1) {
		numLine++;
		if (flagsInfo->l_files_matched) {
			if (SearchPattern(line, pattern, flagsInfo)) {
				if (flagsInfo->c_count) {
					if (numFiles != 1) 
						fprintf(stdout, "%s:1\n", file_name);
					else 
						fprintf(stdout, "1\n");
				}
				fprintf(stdout, "%s\n", file_name);
				break;
			}
		}
		else {
			if (SearchPattern(line, pattern, flagsInfo)) {
				if (!flagsInfo->c_count) {
					if (!flagsInfo->h_no_file_name) {
						if (!flagsInfo->n_line_number) {
							if (!flagsInfo->o_only_matching) {
								if (numFiles!=1)
									fprintf(stdout, "%s:%s\n", file_name, line);
								else
									fprintf(stdout, "%s\n", line);
							}
							else {
								if (numFiles!=1)
									fprintf(stdout, "%s:%s\n", file_name, pattern);
								else
									fprintf(stdout, "%s\n", pattern);
							}
						}
						else {
							if (!flagsInfo->o_only_matching) {
								if (numFiles!=1)
									fprintf(stdout, "%s:%d:%s\n", file_name, lineNum, line);
								else
									fprintf(stdout, "%d:%s\n", lineNum, line);
							}
							else {
								if (numFiles!=1)
									fprintf(stdout, "%s:%d:%s\n", file_name, lineNum, pattern);
								else
									fprintf(stdout, "%d:%s\n", lineNum, pattern);
							}
						}
					}
					else {
						if (!flagsInfo->n_line_number) {
							if (!flagsInfo->o_only_matching) {
								fprintf(stdout, "%s\n", line);
							}
							else {
								fprintf(stdout, "%s\n", pattern);
							}
						}
						else {
							if (!flagsInfo->o_only_matching) {
								fprintf(stdout, "%d:%s\n", lineNum, line);
							}
							else {
								fprintf(stdout, "%d:%s\n",lineNum, pattern);
							}
						}
					}
				}
				else numMatched++;
			}
		}
	}
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
