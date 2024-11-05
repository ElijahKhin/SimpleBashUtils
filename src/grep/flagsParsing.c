#include "s21_grep.h"

static void GetFlags(char* flag, flags* flagsInfo) {
	if (!strcmp("-", flag)) { fprintf(stdout, "%s\n", ERROR_STDIN); exit(1); }
	for (int i = 1; flag[i]; i++) {
		if (flag[i] == 'e') flagsInfo->e_pattern = 1; 
		else if (flag[i] == 'i') flagsInfo->i_ignore_case = 1;
		else if (flag[i] == 'v') flagsInfo->v_invert = 1;
		else if (flag[i] == 'c') flagsInfo->c_count = 1;
		else if (flag[i] == 'l') flagsInfo->l_files_matched = 1;
		else if (flag[i] == 'n') flagsInfo->n_line_number = 1;
		else if (flag[i] == 'h') flagsInfo->h_no_file_name = 1;
		else if (flag[i] == 's') flagsInfo->s_no_messages = 1;
		else if (flag[i] == 'f') flagsInfo->f_file_with_patterns = 1;
		else if (flag[i] == 'o') flagsInfo->o_only_matching = 1;
		else { fprintf(stderr, "%s%c\n%s", ERROR_NO_FLAG, flag[i], USAGE); exit(1);}
	}
}

void ParseFlags(int argc, char*** argv, flags* flagsInfo, files* filesInfo) {
	int numFiles = 0;
	for(int i = 1; i < argc; i++) {
		if ((*argv)[i][0] == '-') GetFlags((*argv)[i], flagsInfo);
		else filesInfo->idxPatternFiles[numFiles++] = i;
	}
	if (!filesInfo->idxPatternFiles[0]) {
		fprintf(stderr, ERROR_NO_FILE), exit(1); 
	}
	filesInfo->numFiles = numFiles-1;
}
