#include "s21_grep.h"

static void GetFlags(char* flag, flags* inputInfo) {
	if (!strcmp("-", flag)) { fprintf(stdout, "%s\n", ERROR_STDIN); exit(1); }
	for (int i = 1; flag[i]; i++) {
		if (flag[i] == 'e') inputInfo->e_pattern = 1; 
		else if (flag[i] == 'i') inputInfo->i_ignore_case = 1;
		else if (flag[i] == 'v') inputInfo->v_invert = 1;
		else if (flag[i] == 'c') inputInfo->c_count = 1;
		else if (flag[i] == 'l') inputInfo->l_files_matched = 1;
		else if (flag[i] == 'n') inputInfo->n_line_number = 1;
		else if (flag[i] == 'h') inputInfo->h_no_file_name = 1;
		else if (flag[i] == 's') inputInfo->s_no_messages = 1;
		else if (flag[i] == 'f') inputInfo->f_file_with_patterns = 1;
		else if (flag[i] == 'o') inputInfo->o_only_matching = 1;
		else { fprintf(stderr, "%s%c\n%s", ERROR_NO_FLAG, flag[i], USAGE); exit(1);}
	}
}

//static void ExcludeIncompatibleFlags(flags* inputInfo) {
//	if (inputInfo->rowNumNonblank == 1 && inputInfo->rowNum == 1) 
//		inputInfo->rowNum = 0;
//}

int ParseFlags(int argc, int* idxPatternFiles, char*** argv, flags* inputInfo) {
	int pf_idx = 0;
	for(int i = 1; i < argc; i++) {
		if ((*argv)[i][0] == '-') GetFlags((*argv)[i], inputInfo);
		else idxPatternFiles[pf_idx++] = i;
	}
	if (!idxPatternFiles[0]) { fprintf(stderr, ERROR_NO_FILE), exit(1); }
	return pf_idx;
//	ExcludeIncompatibleFlags(inputInfo);
}
