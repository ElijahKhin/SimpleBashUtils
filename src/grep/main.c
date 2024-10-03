#include "s21_grep.h"

static void printFlags(flags* inputInfo, int idxPatternFiles[]) {
	printf("pattern: %d\n", inputInfo->e_pattern);
	printf("ignore_case: %d\n", inputInfo->i_ignore_case);
	printf("invert: %d\n", inputInfo->v_invert);
	printf("count: %d\n", inputInfo->c_count);
	printf("files_matched: %d\n", inputInfo->l_files_matched);
	printf("line_number: %d\n", inputInfo->n_line_number);
	printf("no_file_name: %d\n", inputInfo->h_no_file_name);
	printf("no_messages: %d\n", inputInfo->s_no_messages);
	printf("file_with_patterns: %d\n", inputInfo->f_file_with_patterns);
	printf("only_matching: %d\n", inputInfo->o_only_matching);

	printf("pattern_or_first_file_idx: %d\n", idxPatternFiles[0]);
	printf("first_file_idx: %d\n", idxPatternFiles[1]);
	printf("second_file_idx: %d\n", idxPatternFiles[2]);
	printf("one_more_file_idx: %d\n", idxPatternFiles[3]);
}

int main(int argc, char* argv[]) {
	flags inputInfo = {0};
	int* idxPatternFiles;
	idxPatternFiles = (int*)malloc((argc - 1) * sizeof(int));

	if (argc == 1) { fprintf(stderr, ERROR_NO_ARGS); exit(1); }
	ParseFlags(argc, idxPatternFiles, &argv, &inputInfo);
	printFlags(&inputInfo, idxPatternFiles);
//	FilesProcessing(argc, flagIndex, &argv, &inputInfo);
	free(idxPatternFiles);
	return argc;
}
