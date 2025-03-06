#include <string.h>
#include <iomanip>
#include <gtest/gtest.h>
#include <fstream>
#include "s21_grep.h"

void freeTab(char **tab) {
	for (int i = 0; tab[i] != NULL; ++i)
		free(tab[i]);
	free(tab);
}

TEST (PreparePatterns4Parsing, PIN1) {
	int argc = 3, i = 1, j = 1;
	char **argv = s21_split("./s21_grep -epattern file_name", ' ');
	Regex patterns;

	patterns.pnum = 0;
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));

	PreparePatterns4Parsing(argc, &argv, &patterns, &i, j);	
	ASSERT_EQ(patterns.efidx[0], 'e');
	ASSERT_EQ(patterns.efidx[1], 2);
	ASSERT_EQ(patterns.efidx[2], 1);

	freeTab(argv);
	free(patterns.efidx);
}

TEST (PreparePatterns4Parsing, PIN4) {
	int argc = 3, i = 1, j = 3;
	char **argv = s21_split("./s21_grep -siepattern file_name", ' ');
	Regex patterns;

	patterns.pnum = 0;
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));

	PreparePatterns4Parsing(argc, &argv, &patterns, &i, j);	
	ASSERT_EQ(patterns.efidx[0], 'e');
	ASSERT_EQ(patterns.efidx[1], 4);
	ASSERT_EQ(patterns.efidx[2], 1);

	freeTab(argv);
	free(patterns.efidx);
}

TEST (PreparePatterns4Parsing, POUT) {
	int argc = 4, i = 1, j = 1;
	char **argv = s21_split("./s21_grep -f pattern file_name", ' ');
	Regex patterns;

	patterns.pnum = 0;
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));

	PreparePatterns4Parsing(argc, &argv, &patterns, &i, j);	
	ASSERT_EQ(patterns.efidx[0], 'f');
	ASSERT_EQ(patterns.efidx[1], 0);
	ASSERT_EQ(patterns.efidx[2], 2);

	freeTab(argv);
	free(patterns.efidx);
}

//TEST (PreparePatterns4Parsing, CRASH) {
//	int argc = 3, i = 2, j = 1;
//	char **argv = s21_split("./s21_grep file_name -f " , ' ');
//	Regex patterns;
////	FILE* file;
//
//	patterns.pnum = 0;
//	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));
//
//  EXPECT_EXIT(PreparePatterns4Parsing(argc, &argv, &patterns, &i, j), 
//			::testing::ExitedWithCode(1), "grep: option requires an argument -- f");
//
//	freeTab(argv);
//	free(patterns.efidx);
//}

TEST (GetFlagInfo, EOUT) {
	int argc = 4, i = 1;
	char **argv = s21_split("./s21_grep -e pattern file_name" , ' ');
	Flags flags;
	Regex patterns;

	patterns.pnum = 0;
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));
	GetFlagInfo(argc, &argv, &i, &flags, &patterns);	
	ASSERT_EQ(patterns.efidx[0], 'e');
	ASSERT_EQ(patterns.efidx[1], 0);
	ASSERT_EQ(patterns.efidx[2], 2);

	freeTab(argv);
	free(patterns.efidx);
}

TEST (GetFlagInfo, EIN) {
	int argc = 3, i = 1;
	char **argv = s21_split("./s21_grep -epattern file_name" , ' ');
	Flags flags;
	Regex patterns;

	patterns.pnum = 0;
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));
	GetFlagInfo(argc, &argv, &i, &flags, &patterns);	
	ASSERT_EQ(patterns.efidx[0], 'e');
	ASSERT_EQ(patterns.efidx[1], 2);
	ASSERT_EQ(patterns.efidx[2], 1);

	freeTab(argv);
	free(patterns.efidx);
}

TEST (GetFlagInfo, FOUT) {
	int argc = 4, i = 1;
	char **argv = s21_split("./s21_grep -f pattern file_name" , ' ');
	Flags flags;
	Regex patterns;

	patterns.pnum = 0;
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));
	GetFlagInfo(argc, &argv, &i, &flags, &patterns);	
	ASSERT_EQ(patterns.efidx[0], 'f');
	ASSERT_EQ(patterns.efidx[1], 0);
	ASSERT_EQ(patterns.efidx[2], 2);

	freeTab(argv);
	free(patterns.efidx);
}

TEST (GetFlagInfo, FIN) {
	int argc = 3, i = 1;
	char **argv = s21_split("./s21_grep -fpattern file_name" , ' ');
	Flags flags;
	Regex patterns;

	patterns.pnum = 0;
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));
	GetFlagInfo(argc, &argv, &i, &flags, &patterns);	
	ASSERT_EQ(patterns.efidx[0], 'f');
	ASSERT_EQ(patterns.efidx[1], 2);
	ASSERT_EQ(patterns.efidx[2], 1);

	freeTab(argv);
	free(patterns.efidx);
}

TEST (GetFlagInfo, I) {
	int argc = 4, i = 1;
	char **argv = s21_split("./s21_grep -i pattern file_name" , ' ');
	Flags flags = {0};
	Regex patterns;

	patterns.pnum = 0;
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));
	GetFlagInfo(argc, &argv, &i, &flags, &patterns);	
	ASSERT_EQ(flags.i, 1);
	ASSERT_EQ(flags.v, 0);
	ASSERT_EQ(flags.c, 0);
	ASSERT_EQ(flags.l, 0);
	ASSERT_EQ(flags.n, 0);
	ASSERT_EQ(flags.h, 0);
	ASSERT_EQ(flags.s, 0);
	ASSERT_EQ(flags.o, 0);

	freeTab(argv);
	free(patterns.efidx);
}

TEST (GetFlagInfo, V) {
	int argc = 4, i = 1;
	char **argv = s21_split("./s21_grep -v pattern file_name" , ' ');
	Flags flags = {0};
	Regex patterns;

	patterns.pnum = 0;
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));
	GetFlagInfo(argc, &argv, &i, &flags, &patterns);	
	ASSERT_EQ(flags.i, 0);
	ASSERT_EQ(flags.v, 1);
	ASSERT_EQ(flags.c, 0);
	ASSERT_EQ(flags.l, 0);
	ASSERT_EQ(flags.n, 0);
	ASSERT_EQ(flags.h, 0);
	ASSERT_EQ(flags.s, 0);
	ASSERT_EQ(flags.o, 0);

	freeTab(argv);
	free(patterns.efidx);
}

TEST (GetFlagInfo, C) {
	int argc = 4, i = 1;
	char **argv = s21_split("./s21_grep -c pattern file_name" , ' ');
	Flags flags = {0};
	Regex patterns;

	patterns.pnum = 0;
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));
	GetFlagInfo(argc, &argv, &i, &flags, &patterns);	
	ASSERT_EQ(flags.i, 0);
	ASSERT_EQ(flags.v, 0);
	ASSERT_EQ(flags.c, 1);
	ASSERT_EQ(flags.l, 0);
	ASSERT_EQ(flags.n, 0);
	ASSERT_EQ(flags.h, 0);
	ASSERT_EQ(flags.s, 0);
	ASSERT_EQ(flags.o, 0);

	freeTab(argv);
	free(patterns.efidx);
}

TEST (GetFlagInfo, L) {
	int argc = 4, i = 1;
	char **argv = s21_split("./s21_grep -l pattern file_name" , ' ');
	Flags flags = {0};
	Regex patterns;

	patterns.pnum = 0;
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));
	GetFlagInfo(argc, &argv, &i, &flags, &patterns);	
	ASSERT_EQ(flags.i, 0);
	ASSERT_EQ(flags.v, 0);
	ASSERT_EQ(flags.c, 0);
	ASSERT_EQ(flags.l, 1);
	ASSERT_EQ(flags.n, 0);
	ASSERT_EQ(flags.h, 0);
	ASSERT_EQ(flags.s, 0);
	ASSERT_EQ(flags.o, 0);

	freeTab(argv);
	free(patterns.efidx);
}

TEST (GetFlagInfo, N) {
	int argc = 4, i = 1;
	char **argv = s21_split("./s21_grep -n pattern file_name" , ' ');
	Flags flags = {0};
	Regex patterns;

	patterns.pnum = 0;
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));
	GetFlagInfo(argc, &argv, &i, &flags, &patterns);	
	ASSERT_EQ(flags.i, 0);
	ASSERT_EQ(flags.v, 0);
	ASSERT_EQ(flags.c, 0);
	ASSERT_EQ(flags.l, 0);
	ASSERT_EQ(flags.n, 1);
	ASSERT_EQ(flags.h, 0);
	ASSERT_EQ(flags.s, 0);
	ASSERT_EQ(flags.o, 0);

	freeTab(argv);
	free(patterns.efidx);
}

TEST (GetFlagInfo, H) {
	int argc = 4, i = 1;
	char **argv = s21_split("./s21_grep -h pattern file_name" , ' ');
	Flags flags = {0};
	Regex patterns;

	patterns.pnum = 0;
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));
	GetFlagInfo(argc, &argv, &i, &flags, &patterns);	
	ASSERT_EQ(flags.i, 0);
	ASSERT_EQ(flags.v, 0);
	ASSERT_EQ(flags.c, 0);
	ASSERT_EQ(flags.l, 0);
	ASSERT_EQ(flags.n, 0);
	ASSERT_EQ(flags.h, 1);
	ASSERT_EQ(flags.s, 0);
	ASSERT_EQ(flags.o, 0);

	freeTab(argv);
	free(patterns.efidx);
}

TEST (GetFlagInfo, S) {
	int argc = 4, i = 1;
	char **argv = s21_split("./s21_grep -s pattern file_name" , ' ');
	Flags flags = {0};
	Regex patterns;

	patterns.pnum = 0;
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));
	GetFlagInfo(argc, &argv, &i, &flags, &patterns);	
	ASSERT_EQ(flags.i, 0);
	ASSERT_EQ(flags.v, 0);
	ASSERT_EQ(flags.c, 0);
	ASSERT_EQ(flags.l, 0);
	ASSERT_EQ(flags.n, 0);
	ASSERT_EQ(flags.h, 0);
	ASSERT_EQ(flags.s, 1);
	ASSERT_EQ(flags.o, 0);

	freeTab(argv);
	free(patterns.efidx);
}

TEST (GetFlagInfo, O) {
	int argc = 4, i = 1;
	char **argv = s21_split("./s21_grep -o pattern file_name" , ' ');
	Flags flags = {0};
	Regex patterns;

	patterns.pnum = 0;
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));
	GetFlagInfo(argc, &argv, &i, &flags, &patterns);	
	ASSERT_EQ(flags.i, 0);
	ASSERT_EQ(flags.v, 0);
	ASSERT_EQ(flags.c, 0);
	ASSERT_EQ(flags.l, 0);
	ASSERT_EQ(flags.n, 0);
	ASSERT_EQ(flags.h, 0);
	ASSERT_EQ(flags.s, 0);
	ASSERT_EQ(flags.o, 1);

	freeTab(argv);
	free(patterns.efidx);
}

//TEST (GetFlagInfo, CRASH) {
//	int argc = 4, i = 1;
//	char **argv = s21_split("./s21_grep -ia pattern file_name" , ' ');
//	Flags flags = {0};
//	Regex patterns;
////	FILE* file;
//
//	patterns.pnum = 0;
//	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));
//
//	;	
//  EXPECT_EXIT(GetFlagInfo(argc, &argv, &i, &flags, &patterns), 
//			::testing::ExitedWithCode(1), ERROR_NO_FLAG);
//
//	freeTab(argv);
//	free(patterns.efidx);
//}


TEST (Alloc4F, EMPTY_FILE) {
	int len = 0;
	char* file_name = "test_files/empty_file";
	Regex patterns;
	patterns.file_emp = 0;

	Alloc4F(&len, file_name, &patterns); 
	ASSERT_EQ(len, 0);
	ASSERT_EQ(patterns.file_emp, 1);
}

TEST (Alloc4F, EMPTY_PATTERN) {
	int len = 0;
	char* file_name = "test_files/empty_patt";
	Regex patterns;
	patterns.patt_emp = 0;

	Alloc4F(&len, file_name, &patterns); 
	ASSERT_EQ(len, 0);
	ASSERT_EQ(patterns.patt_emp, 1);
}

TEST (Alloc4F, SEVERAL_PATTERNS) {
	int len = 0;
	char* file_name = "test_files/multi_patt";
	Regex patterns;
	patterns.file_emp = 0;
	patterns.patt_emp = 0;

	Alloc4F(&len, file_name, &patterns);
	ASSERT_EQ(len, 25);
	ASSERT_EQ(patterns.file_emp, 0);
	ASSERT_EQ(patterns.patt_emp, 0);
}

TEST (Alloc4E, EMPTY_PATTERN) {
	int len = 0;
	char* pattern = "";
	Regex patterns;
	patterns.patt_emp = 0;
	patterns.file_emp = 0;

	Alloc4E(&len, pattern, &patterns); 
	ASSERT_EQ(len, 0);
	ASSERT_EQ(patterns.patt_emp, 1);
	ASSERT_EQ(patterns.file_emp, 0);
}

TEST (Alloc4E, BASIC_PATTERN) {
	int len = 0;
	char* pattern = "pattern";
	Regex patterns;
	patterns.patt_emp = 0;
	patterns.file_emp = 0;

	Alloc4E(&len, pattern, &patterns); 
	ASSERT_EQ(len, 8);
	ASSERT_EQ(patterns.patt_emp, 0);
	ASSERT_EQ(patterns.file_emp, 0);
}

TEST (AllocFullPattern, E_EMPTY) {
	char **argv;
	argv = (char **)malloc(sizeof(char *) * 5);

	argv[0] = (char *)malloc(100);
	argv[1] = (char *)malloc(100);
	argv[2] = (char *)malloc(100);
	argv[3] = (char *)malloc(100);

	strcpy(argv[0], "./s21_grep");
	strcpy(argv[1], "-e");
	strcpy(argv[2], "");
	strcpy(argv[3],"file_name");

	Regex patterns;
	patterns.pnum = 3;
	patterns.efidx = (int *)malloc(3 * sizeof(int));
	patterns.efidx[0] = 'e';
	patterns.efidx[1] = 0;
	patterns.efidx[2] = 2;

	ASSERT_EQ(AllocFullPattern(&argv, &patterns), 0);
	ASSERT_EQ(patterns.patt_emp, 1);
	ASSERT_EQ(patterns.file_emp, 0);


	freeTab(argv);
	free(patterns.efidx);
}

TEST (AllocFullPattern, E_SEVERAL) {
	char **argv = s21_split("./s21_grep -e pat1 -e pat2pat2 file_name", ' ');

	Regex patterns;
	patterns.pnum = 6;
	patterns.efidx = (int *)malloc(6 * sizeof(int));
	patterns.efidx[0] = 'e';
	patterns.efidx[1] = 0;
	patterns.efidx[2] = 2;
	patterns.efidx[3] = 'e';
	patterns.efidx[4] = 0;
	patterns.efidx[5] = 4;

	ASSERT_EQ(AllocFullPattern(&argv, &patterns), 1);
	ASSERT_EQ(patterns.patt_emp, 0);
	ASSERT_EQ(patterns.file_emp, 0);


	freeTab(argv);
	free(patterns.efidx);
	free(patterns.full_pattern);
}

TEST (AllocFullPattern, F_EMPTY_FILE) {
	char **argv;
	argv = (char **)malloc(sizeof(char *) * 5);
	char* file_name = "";

	argv[0] = (char *)malloc(100);
	argv[1] = (char *)malloc(100);
	argv[2] = (char *)malloc(100);
	argv[3] = (char *)malloc(100);

	strcpy(argv[0], "./s21_grep");
	strcpy(argv[1], "-f");
	strcpy(argv[2], "test_files/empty_file");
	strcpy(argv[3],"file_name");

	Regex patterns;
	patterns.pnum = 3;
	patterns.efidx = (int *)malloc(6 * sizeof(int));
	patterns.efidx[0] = 'f';
	patterns.efidx[1] = 0;
	patterns.efidx[2] = 2;

	ASSERT_EQ(AllocFullPattern(&argv, &patterns), 0);
	ASSERT_EQ(patterns.patt_emp, 0);
	ASSERT_EQ(patterns.file_emp, 1);


	freeTab(argv);
	free(patterns.efidx);
}

TEST (AllocFullPattern, F_EMPTY_PATTERN) {
	char **argv;
	argv = (char **)malloc(sizeof(char *) * 5);
	char* file_name = "";

	argv[0] = (char *)malloc(100);
	argv[1] = (char *)malloc(100);
	argv[2] = (char *)malloc(100);
	argv[3] = (char *)malloc(100);

	strcpy(argv[0], "./s21_grep");
	strcpy(argv[1], "-f");
	strcpy(argv[2], "test_files/empty_patt");
	strcpy(argv[3],"file_name");

	Regex patterns;
	patterns.pnum = 3;
	patterns.efidx = (int *)malloc(6 * sizeof(int));
	patterns.efidx[0] = 'f';
	patterns.efidx[1] = 0;
	patterns.efidx[2] = 2;

	ASSERT_EQ(AllocFullPattern(&argv, &patterns), 0);
	ASSERT_EQ(patterns.patt_emp, 1);
	ASSERT_EQ(patterns.file_emp, 0);


	freeTab(argv);
	free(patterns.efidx);
}

TEST (AllocFullPattern, F_SEVERAL_PATTERNS) {
	char **argv;
	argv = (char **)malloc(sizeof(char *) * 5);
	char* file_name = "";

	argv[0] = (char *)malloc(100);
	argv[1] = (char *)malloc(100);
	argv[2] = (char *)malloc(100);
	argv[3] = (char *)malloc(100);

	strcpy(argv[0], "./s21_grep");
	strcpy(argv[1], "-f");
	strcpy(argv[2], "test_files/multi_patt");
	strcpy(argv[3],"file_name");

	Regex patterns;
	patterns.pnum = 3;
	patterns.efidx = (int *)malloc(6 * sizeof(int));
	patterns.efidx[0] = 'f';
	patterns.efidx[1] = 0;
	patterns.efidx[2] = 2;

	ASSERT_EQ(AllocFullPattern(&argv, &patterns), 1);
	ASSERT_EQ(patterns.patt_emp, 0);
	ASSERT_EQ(patterns.file_emp, 0);

	freeTab(argv);
	free(patterns.efidx);
	free(patterns.full_pattern);
}

TEST (GetPrintOption, EMPTY_PATTERN1) {
	Flags flags;
	Regex patterns;

	patterns.patt_emp = patterns.file_emp = 1;
	flags.v = flags.o = 0;
	GetPrintOption(0, &patterns, &flags);
	ASSERT_EQ(patterns.print_opt, 1);
}

TEST (GetPrintOption, EMPTY_PATTERN0) {
	Flags flags;
	Regex patterns;

	patterns.patt_emp = patterns.file_emp = 1;
	flags.v = 0;
	flags.o = 1;
	GetPrintOption(0, &patterns, &flags);
	ASSERT_EQ(patterns.print_opt, 0);

	patterns.patt_emp = patterns.file_emp = 1;
	flags.v = 1;
	flags.o = 0;
	GetPrintOption(0, &patterns, &flags);
	ASSERT_EQ(patterns.print_opt, 0);
}

TEST (GetPrintOption, EMPTY_FILE) {
	Flags flags;
	Regex patterns;

	patterns.patt_emp = 0;
	patterns.file_emp = 1;
	flags.v = 0;
	flags.o = 1;
	GetPrintOption(0, &patterns, &flags);
	ASSERT_EQ(patterns.print_opt, 0);

	patterns.patt_emp = 0;
	patterns.file_emp = 1;
	flags.v = 1;
	flags.o = 0;
	GetPrintOption(0, &patterns, &flags);
	ASSERT_EQ(patterns.print_opt, 1);

	patterns.patt_emp = 0;
	patterns.file_emp = 1;
	flags.v = 1;
	flags.o = 0;
	GetPrintOption(1, &patterns, &flags);
	ASSERT_EQ(patterns.print_opt, 2);

	patterns.patt_emp = 0;
	patterns.file_emp = 1;
	flags.v = 0;
	flags.o = 0;
	GetPrintOption(0, &patterns, &flags);
	ASSERT_EQ(patterns.print_opt, 0);
}

TEST (GetPrintOption, NORMAL) {
	Flags flags;
	Regex patterns;

	patterns.patt_emp = 0;
	patterns.file_emp = 0;
	flags.v = 1;
	flags.o = 1;
	GetPrintOption(1, &patterns, &flags);
	ASSERT_EQ(patterns.print_opt, 2);

	patterns.patt_emp = 0;
	patterns.file_emp = 0;
	flags.v = 0;
	flags.o = 0;
	GetPrintOption(1, &patterns, &flags);
	ASSERT_EQ(patterns.print_opt, 2);
}

TEST (ConcatPattern, E_ONE) {
	Regex patterns;
	char **argv = s21_split("./s21_grep -e pattern1 file_name", ' ');

	patterns.pnum = 3;
	patterns.efidx = (int *)malloc(3 * sizeof(int));
	patterns.efidx[0] = 'e';
	patterns.efidx[1] = 0;
	patterns.efidx[2] = 2;
	patterns.full_pattern = (char *)malloc(9);

	ConcatPattern(&argv, &patterns);

	ASSERT_EQ(strcmp(patterns.full_pattern, "pattern1"), 0);

	freeTab(argv);
	free(patterns.efidx);
	free(patterns.full_pattern);
}

TEST (ConcatPattern, E_SEVERAL) {
	Regex patterns;
	char **argv = s21_split("./s21_grep -e pattern1 -e pattern2 -e pattern3 file_name", ' ');

	patterns.pnum = 9;
	patterns.efidx = (int *)malloc(9 * sizeof(int));
	patterns.efidx[0] = 'e';
	patterns.efidx[1] = 0;
	patterns.efidx[2] = 2;
	patterns.efidx[3] = 'e';
	patterns.efidx[4] = 0;
	patterns.efidx[5] = 4;
	patterns.efidx[6] = 'e';
	patterns.efidx[7] = 0;
	patterns.efidx[8] = 6;
	patterns.full_pattern = (char *)malloc(27);

	ConcatPattern(&argv, &patterns);
	
	ASSERT_EQ(strcmp(patterns.full_pattern, "pattern1|pattern2|pattern3"), 0);

	freeTab(argv);
	free(patterns.efidx);
	free(patterns.full_pattern);
}

TEST (ConcatPattern, F_ONE) {
	Regex patterns;
	char **argv = s21_split("./s21_grep -f test_files/multi_patt file_name", ' ');

	patterns.pnum = 3;
	patterns.efidx = (int *)malloc(3 * sizeof(int));
	patterns.efidx[0] = 'f';
	patterns.efidx[1] = 0;
	patterns.efidx[2] = 2;
	patterns.full_pattern = (char *)malloc(25);

	ConcatPattern(&argv, &patterns);

	ASSERT_EQ(strcmp(patterns.full_pattern, "-|pat1|pat2|pat3|dummy|a"), 0);

	freeTab(argv);
	free(patterns.efidx);
	free(patterns.full_pattern);
}

TEST (ConcatPattern, F_SEVERAL) {
	Regex patterns;
	char **argv = s21_split("./s21_grep -f test_files/multi_patt -f test_files/multi_patt -f test_files/multi_patt file_name", ' ');

	patterns.pnum = 9;
	patterns.efidx = (int *)malloc(9 * sizeof(int));
	patterns.efidx[0] = 'f';
	patterns.efidx[1] = 0;
	patterns.efidx[2] = 2;
	patterns.efidx[3] = 'f';
	patterns.efidx[4] = 0;
	patterns.efidx[5] = 4;
	patterns.efidx[6] = 'f';
	patterns.efidx[7] = 0;
	patterns.efidx[8] = 6;
	patterns.full_pattern = (char *)malloc(75);

	ConcatPattern(&argv, &patterns);
	
	ASSERT_EQ(strcmp(patterns.full_pattern, "-|pat1|pat2|pat3|dummy|a|-|pat1|pat2|pat3|dummy|a|-|pat1|pat2|pat3|dummy|a"), 0);

	freeTab(argv);
	free(patterns.efidx);
	free(patterns.full_pattern);
}

TEST (ConcatPattern, FE_ONE) {
	char **argv = s21_split("./s21_grep -f test_files/multi_patt -e pattern1 file_name", ' ');

	Regex patterns;
	patterns.pnum = 6;
	patterns.efidx = (int *)malloc(6 * sizeof(int));
	patterns.efidx[0] = 'f';
	patterns.efidx[1] = 0;
	patterns.efidx[2] = 2;
	patterns.efidx[3] = 'e';
	patterns.efidx[4] = 0;
	patterns.efidx[5] = 4;
	patterns.full_pattern = (char *)malloc(33);

	ConcatPattern(&argv, &patterns);

	ASSERT_EQ(strcmp(patterns.full_pattern, "-|pat1|pat2|pat3|dummy|a|pattern1"), 0);

	freeTab(argv);
	free(patterns.efidx);
	free(patterns.full_pattern);
}

TEST (ConcatPattern, FE_SEVERAL) {
	Regex patterns;
	char **argv = s21_split("./s21_grep -f test_files/multi_patt -f test_files/multi_patt -f test_files/multi_patt -e pattern1 -e pattern2 file_name", ' ');

	patterns.pnum = 15;
	patterns.efidx = (int *)malloc(15 * sizeof(int));
	patterns.efidx[0] = 'f';
	patterns.efidx[1] = 0;
	patterns.efidx[2] = 2;
	patterns.efidx[3] = 'f';
	patterns.efidx[4] = 0;
	patterns.efidx[5] = 4;
	patterns.efidx[6] = 'f';
	patterns.efidx[7] = 0;
	patterns.efidx[8] = 6;
	patterns.efidx[9] = 'e';
	patterns.efidx[10] = 0;
	patterns.efidx[11] = 8;
	patterns.efidx[12] = 'e';
	patterns.efidx[13] = 0;
	patterns.efidx[14] = 10;
	patterns.full_pattern = (char *)malloc(93);

	ConcatPattern(&argv, &patterns);
	
	ASSERT_EQ(strcmp(patterns.full_pattern, "-|pat1|pat2|pat3|dummy|a|-|pat1|pat2|pat3|dummy|a|-|pat1|pat2|pat3|dummy|a|pattern1|pattern2"), 0);

	freeTab(argv);
	free(patterns.efidx);
	free(patterns.full_pattern);
}

TEST (ParseFlags, WO_Flags) {
	Flags flags = {0};
	Map map;
	Regex patterns;
	int argc = 3;
	char **argv = s21_split("./s21_grep pattern file_name" , ' ');

	map.mnum = 0;
	patterns.pnum = 0;
	map.whoiswho = (int*)malloc((argc - 1) * sizeof(int));
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));


	ParseFlags(argc, &argv, &flags, &map, &patterns);

	ASSERT_EQ(flags.i, 0);
	ASSERT_EQ(flags.v, 0);
	ASSERT_EQ(flags.c, 0);
	ASSERT_EQ(flags.l, 0);
	ASSERT_EQ(flags.n, 0);
	ASSERT_EQ(flags.h, 0);
	ASSERT_EQ(flags.s, 0);
	ASSERT_EQ(flags.o, 0);

	ASSERT_EQ(map.mnum, 2);
	ASSERT_EQ(map.whoiswho[0], 1);
	ASSERT_EQ(map.whoiswho[1], 2);

	ASSERT_EQ(patterns.pnum, 0);
	ASSERT_EQ(patterns.efidx[0], NULL);

	freeTab(argv);
	free(map.whoiswho);
	free(patterns.efidx);
	regfree(&patterns.regex);
}

TEST (ParseFlags, BASIC_I) {
	Flags flags = {0};
	Map map;
	Regex patterns;
	int argc = 4;
	char **argv = s21_split("./s21_grep -i pattern file_name" , ' ');

	map.mnum = 0;
	patterns.pnum = 0;
	map.whoiswho = (int*)malloc((argc - 1) * sizeof(int));
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));


	ParseFlags(argc, &argv, &flags, &map, &patterns);

	ASSERT_EQ(flags.i, 1);
	ASSERT_EQ(flags.v, 0);
	ASSERT_EQ(flags.c, 0);
	ASSERT_EQ(flags.l, 0);
	ASSERT_EQ(flags.n, 0);
	ASSERT_EQ(flags.h, 0);
	ASSERT_EQ(flags.s, 0);
	ASSERT_EQ(flags.o, 0);

	ASSERT_EQ(map.mnum, 2);
	ASSERT_EQ(map.whoiswho[0], 2);
	ASSERT_EQ(map.whoiswho[1], 3);

	ASSERT_EQ(patterns.pnum, 0);
	ASSERT_EQ(patterns.efidx[0], NULL);

	freeTab(argv);
	free(map.whoiswho);
	free(patterns.efidx);
	regfree(&patterns.regex);
}

TEST (ParseFlags, BASIC_V) {
	Flags flags = {0};
	Map map;
	Regex patterns;
	int argc = 4;
	char **argv = s21_split("./s21_grep -v pattern file_name" , ' ');

	map.mnum = 0;
	patterns.pnum = 0;
	map.whoiswho = (int*)malloc((argc - 1) * sizeof(int));
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));


	ParseFlags(argc, &argv, &flags, &map, &patterns);

	ASSERT_EQ(flags.i, 0);
	ASSERT_EQ(flags.v, 1);
	ASSERT_EQ(flags.c, 0);
	ASSERT_EQ(flags.l, 0);
	ASSERT_EQ(flags.n, 0);
	ASSERT_EQ(flags.h, 0);
	ASSERT_EQ(flags.s, 0);
	ASSERT_EQ(flags.o, 0);

	ASSERT_EQ(map.mnum, 2);
	ASSERT_EQ(map.whoiswho[0], 2);
	ASSERT_EQ(map.whoiswho[1], 3);

	ASSERT_EQ(patterns.pnum, 0);
	ASSERT_EQ(patterns.efidx[0], NULL);

	freeTab(argv);
	free(map.whoiswho);
	free(patterns.efidx);
	regfree(&patterns.regex);
}

TEST (ParseFlags, BASIC_C) {
	Flags flags = {0};
	Map map;
	Regex patterns;
	int argc = 4;
	char **argv = s21_split("./s21_grep -c pattern file_name" , ' ');

	map.mnum = 0;
	patterns.pnum = 0;
	map.whoiswho = (int*)malloc((argc - 1) * sizeof(int));
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));


	ParseFlags(argc, &argv, &flags, &map, &patterns);

	ASSERT_EQ(flags.i, 0);
	ASSERT_EQ(flags.v, 0);
	ASSERT_EQ(flags.c, 1);
	ASSERT_EQ(flags.l, 0);
	ASSERT_EQ(flags.n, 0);
	ASSERT_EQ(flags.h, 0);
	ASSERT_EQ(flags.s, 0);
	ASSERT_EQ(flags.o, 0);

	ASSERT_EQ(map.mnum, 2);
	ASSERT_EQ(map.whoiswho[0], 2);
	ASSERT_EQ(map.whoiswho[1], 3);

	ASSERT_EQ(patterns.pnum, 0);
	ASSERT_EQ(patterns.efidx[0], NULL);

	freeTab(argv);
	free(map.whoiswho);
	free(patterns.efidx);
	regfree(&patterns.regex);
}

TEST (ParseFlags, BASIC_L) {
	Flags flags = {0};
	Map map;
	Regex patterns;
	int argc = 4;
	char **argv = s21_split("./s21_grep -l pattern file_name" , ' ');

	map.mnum = 0;
	patterns.pnum = 0;
	map.whoiswho = (int*)malloc((argc - 1) * sizeof(int));
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));


	ParseFlags(argc, &argv, &flags, &map, &patterns);

	ASSERT_EQ(flags.i, 0);
	ASSERT_EQ(flags.v, 0);
	ASSERT_EQ(flags.c, 0);
	ASSERT_EQ(flags.l, 1);
	ASSERT_EQ(flags.n, 0);
	ASSERT_EQ(flags.h, 0);
	ASSERT_EQ(flags.s, 0);
	ASSERT_EQ(flags.o, 0);

	ASSERT_EQ(map.mnum, 2);
	ASSERT_EQ(map.whoiswho[0], 2);
	ASSERT_EQ(map.whoiswho[1], 3);

	ASSERT_EQ(patterns.pnum, 0);
	ASSERT_EQ(patterns.efidx[0], NULL);

	freeTab(argv);
	free(map.whoiswho);
	free(patterns.efidx);
	regfree(&patterns.regex);
}

TEST (ParseFlags, BASIC_N) {
	Flags flags = {0};
	Map map;
	Regex patterns;
	int argc = 4;
	char **argv = s21_split("./s21_grep -n pattern file_name" , ' ');

	map.mnum = 0;
	patterns.pnum = 0;
	map.whoiswho = (int*)malloc((argc - 1) * sizeof(int));
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));


	ParseFlags(argc, &argv, &flags, &map, &patterns);

	ASSERT_EQ(flags.i, 0);
	ASSERT_EQ(flags.v, 0);
	ASSERT_EQ(flags.c, 0);
	ASSERT_EQ(flags.l, 0);
	ASSERT_EQ(flags.n, 1);
	ASSERT_EQ(flags.h, 0);
	ASSERT_EQ(flags.s, 0);
	ASSERT_EQ(flags.o, 0);

	ASSERT_EQ(map.mnum, 2);
	ASSERT_EQ(map.whoiswho[0], 2);
	ASSERT_EQ(map.whoiswho[1], 3);

	ASSERT_EQ(patterns.pnum, 0);
	ASSERT_EQ(patterns.efidx[0], NULL);

	freeTab(argv);
	free(map.whoiswho);
	free(patterns.efidx);
	regfree(&patterns.regex);
}

TEST (ParseFlags, BASIC_H) {
	Flags flags = {0};
	Map map;
	Regex patterns;
	int argc = 4;
	char **argv = s21_split("./s21_grep -h pattern file_name" , ' ');

	map.mnum = 0;
	patterns.pnum = 0;
	map.whoiswho = (int*)malloc((argc - 1) * sizeof(int));
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));


	ParseFlags(argc, &argv, &flags, &map, &patterns);

	ASSERT_EQ(flags.i, 0);
	ASSERT_EQ(flags.v, 0);
	ASSERT_EQ(flags.c, 0);
	ASSERT_EQ(flags.l, 0);
	ASSERT_EQ(flags.n, 0);
	ASSERT_EQ(flags.h, 1);
	ASSERT_EQ(flags.s, 0);
	ASSERT_EQ(flags.o, 0);

	ASSERT_EQ(map.mnum, 2);
	ASSERT_EQ(map.whoiswho[0], 2);
	ASSERT_EQ(map.whoiswho[1], 3);

	ASSERT_EQ(patterns.pnum, 0);
	ASSERT_EQ(patterns.efidx[0], NULL);

	freeTab(argv);
	free(map.whoiswho);
	free(patterns.efidx);
	regfree(&patterns.regex);
}

TEST (ParseFlags, BASIC_S) {
	Flags flags = {0};
	Map map;
	Regex patterns;
	int argc = 4;
	char **argv = s21_split("./s21_grep -s pattern file_name" , ' ');

	map.mnum = 0;
	patterns.pnum = 0;
	map.whoiswho = (int*)malloc((argc - 1) * sizeof(int));
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));


	ParseFlags(argc, &argv, &flags, &map, &patterns);

	ASSERT_EQ(flags.i, 0);
	ASSERT_EQ(flags.v, 0);
	ASSERT_EQ(flags.c, 0);
	ASSERT_EQ(flags.l, 0);
	ASSERT_EQ(flags.n, 0);
	ASSERT_EQ(flags.h, 0);
	ASSERT_EQ(flags.s, 1);
	ASSERT_EQ(flags.o, 0);

	ASSERT_EQ(map.mnum, 2);
	ASSERT_EQ(map.whoiswho[0], 2);
	ASSERT_EQ(map.whoiswho[1], 3);

	ASSERT_EQ(patterns.pnum, 0);
	ASSERT_EQ(patterns.efidx[0], NULL);

	freeTab(argv);
	free(map.whoiswho);
	free(patterns.efidx);
	regfree(&patterns.regex);
}

TEST (ParseFlags, BASIC_O) {
	Flags flags = {0};
	Map map;
	Regex patterns;
	int argc = 4;
	char **argv = s21_split("./s21_grep -o pattern file_name" , ' ');

	map.mnum = 0;
	patterns.pnum = 0;
	map.whoiswho = (int*)malloc((argc - 1) * sizeof(int));
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));


	ParseFlags(argc, &argv, &flags, &map, &patterns);

	ASSERT_EQ(flags.i, 0);
	ASSERT_EQ(flags.v, 0);
	ASSERT_EQ(flags.c, 0);
	ASSERT_EQ(flags.l, 0);
	ASSERT_EQ(flags.n, 0);
	ASSERT_EQ(flags.h, 0);
	ASSERT_EQ(flags.s, 0);
	ASSERT_EQ(flags.o, 1);

	ASSERT_EQ(map.mnum, 2);
	ASSERT_EQ(map.whoiswho[0], 2);
	ASSERT_EQ(map.whoiswho[1], 3);

	ASSERT_EQ(patterns.pnum, 0);
	ASSERT_EQ(patterns.efidx[0], NULL);

	freeTab(argv);
	free(map.whoiswho);
	free(patterns.efidx);
	regfree(&patterns.regex);
}

TEST (ParseFlags, REGEX_E) {
	Flags flags = {0};
	Map map;
	Regex patterns;
	int argc = 4;
	char **argv = s21_split("./s21_grep -e pattern file_name" , ' ');

	map.mnum = 0;
	patterns.pnum = 0;
	map.whoiswho = (int*)malloc((argc - 1) * sizeof(int));
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));


	ParseFlags(argc, &argv, &flags, &map, &patterns);

	ASSERT_EQ(flags.i, 0);
	ASSERT_EQ(flags.v, 0);
	ASSERT_EQ(flags.c, 0);
	ASSERT_EQ(flags.l, 0);
	ASSERT_EQ(flags.n, 0);
	ASSERT_EQ(flags.h, 0);
	ASSERT_EQ(flags.s, 0);
	ASSERT_EQ(flags.o, 0);

	ASSERT_EQ(map.mnum, 1);
	ASSERT_EQ(map.whoiswho[0], 3);

	ASSERT_EQ(patterns.pnum, 3);
	ASSERT_EQ(patterns.efidx[0], 'e');
	ASSERT_EQ(patterns.efidx[1], 0);
	ASSERT_EQ(patterns.efidx[2], 2);

	freeTab(argv);
	free(map.whoiswho);
	free(patterns.efidx);
	free(patterns.full_pattern);
	regfree(&patterns.regex);
}

TEST (ParseFlags, REGEX_F) {
	Flags flags = {0};
	Map map;
	Regex patterns;
	int argc = 4;
	char **argv = s21_split("./s21_grep -f test_files/multi_patt file_name" , ' ');

	map.mnum = 0;
	patterns.pnum = 0;
	map.whoiswho = (int*)malloc((argc - 1) * sizeof(int));
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));


	ParseFlags(argc, &argv, &flags, &map, &patterns);

	ASSERT_EQ(flags.i, 0);
	ASSERT_EQ(flags.v, 0);
	ASSERT_EQ(flags.c, 0);
	ASSERT_EQ(flags.l, 0);
	ASSERT_EQ(flags.n, 0);
	ASSERT_EQ(flags.h, 0);
	ASSERT_EQ(flags.s, 0);
	ASSERT_EQ(flags.o, 0);

	ASSERT_EQ(map.mnum, 1);
	ASSERT_EQ(map.whoiswho[0], 3);

	ASSERT_EQ(patterns.pnum, 3);
	ASSERT_EQ(patterns.efidx[0], 'f');
	ASSERT_EQ(patterns.efidx[1], 0);
	ASSERT_EQ(patterns.efidx[2], 2);

	free(patterns.full_pattern);
	freeTab(argv);
	free(map.whoiswho);
	free(patterns.efidx);
	regfree(&patterns.regex);
}

TEST (ParseFlags, MULTI) {
	Flags flags = {0};
	Map map;
	Regex patterns;
	int argc = 10;
	char **argv = s21_split("./s21_grep -ftest_files/multi_patt -e pattern2 file_name -epattern3 -f test_files/multi_patt file_name2 -ivsepattern5", ' ');

	map.mnum = 0;
	patterns.pnum = 0;
	map.whoiswho = (int*)malloc((argc - 1) * sizeof(int));
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));


	ParseFlags(argc, &argv, &flags, &map, &patterns);

	ASSERT_EQ(flags.i, 1);
	ASSERT_EQ(flags.v, 1);
	ASSERT_EQ(flags.c, 0);
	ASSERT_EQ(flags.l, 0);
	ASSERT_EQ(flags.n, 0);
	ASSERT_EQ(flags.h, 0);
	ASSERT_EQ(flags.s, 1);
	ASSERT_EQ(flags.o, 0);

	ASSERT_EQ(map.mnum, 2);
	ASSERT_EQ(map.whoiswho[0], 4);
	ASSERT_EQ(map.whoiswho[1], 8);

	ASSERT_EQ(patterns.pnum, 15);
	ASSERT_EQ(patterns.efidx[0], 'f');
	ASSERT_EQ(patterns.efidx[1], 2);
	ASSERT_EQ(patterns.efidx[2], 1);
	ASSERT_EQ(patterns.efidx[3], 'e');
	ASSERT_EQ(patterns.efidx[4], 0);
	ASSERT_EQ(patterns.efidx[5], 3);
	ASSERT_EQ(patterns.efidx[6], 'e');
	ASSERT_EQ(patterns.efidx[7], 2);
	ASSERT_EQ(patterns.efidx[8], 5);
	ASSERT_EQ(patterns.efidx[9], 'f');
	ASSERT_EQ(patterns.efidx[10], 0);
	ASSERT_EQ(patterns.efidx[11], 7);
	ASSERT_EQ(patterns.efidx[12], 'e');
	ASSERT_EQ(patterns.efidx[13], 5);
	ASSERT_EQ(patterns.efidx[14], 9);

	freeTab(argv);
	free(map.whoiswho);
	free(patterns.efidx);
	free(patterns.full_pattern);
	regfree(&patterns.regex);
}

TEST (ParseFlags, DASH) {
	Flags flags = {0};
	Map map;
	Regex patterns;
	int argc = 5;
	char **argv = s21_split("./s21_grep - -iv file_name file_name2" , ' ');

	map.mnum = 0;
	patterns.pnum = 0;
	map.whoiswho = (int*)malloc((argc - 1) * sizeof(int));
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));


	ParseFlags(argc, &argv, &flags, &map, &patterns);

	ASSERT_EQ(flags.i, 1);
	ASSERT_EQ(flags.v, 1);
	ASSERT_EQ(flags.c, 0);
	ASSERT_EQ(flags.l, 0);
	ASSERT_EQ(flags.n, 0);
	ASSERT_EQ(flags.h, 0);
	ASSERT_EQ(flags.s, 0);
	ASSERT_EQ(flags.o, 0);

	ASSERT_EQ(map.mnum, 3);
	ASSERT_EQ(map.whoiswho[0], 1);
	ASSERT_EQ(map.whoiswho[1], 3);
	ASSERT_EQ(map.whoiswho[2], 4);

	ASSERT_EQ(patterns.pnum, 0);
	ASSERT_EQ(patterns.efidx[0], NULL);

	freeTab(argv);
	free(map.whoiswho);
	free(patterns.efidx);
	regfree(&patterns.regex);
}

TEST (ParseFlags, EMPTY_PATTERN_NO_FLAGS) {
	Flags flags = {0};
	Map map;
	Regex patterns;
	int argc = 3;
	char **argv;
	argv = (char **)malloc(sizeof(char *) * 4);

	argv[0] = (char *)malloc(100);
	argv[1] = (char *)malloc(100);
	argv[2] = (char *)malloc(100);

	strcpy(argv[0], "./s21_grep");
	strcpy(argv[1], "");
	strcpy(argv[2],"file_name");

	map.mnum = patterns.pnum = 0;
	map.whoiswho = (int*)malloc((argc - 1) * sizeof(int));


	ParseFlags(argc, &argv, &flags, &map, &patterns);
	ASSERT_EQ(patterns.print_opt, 1);

	freeTab(argv);
	free(map.whoiswho);
}

TEST (ParseFlags, EMPTY_PATTERN_WITH_FLAGS) {
	Flags flags = {0};
	Map map;
	Regex patterns;
	int argc = 3;
	char **argv;
	argv = (char **)malloc(sizeof(char *) * 5);

	argv[0] = (char *)malloc(100);
	argv[1] = (char *)malloc(100);
	argv[2] = (char *)malloc(100);
	argv[3] = (char *)malloc(100);

	strcpy(argv[0], "./s21_grep");
	strcpy(argv[1], "");
	strcpy(argv[2], "-v");
	strcpy(argv[3],"file_name");

	map.mnum = patterns.pnum = 0;
	map.whoiswho = (int*)malloc((argc - 1) * sizeof(int));


	ParseFlags(argc, &argv, &flags, &map, &patterns);
	ASSERT_EQ(patterns.print_opt, 0);

	freeTab(argv);
	free(map.whoiswho);
}

TEST (ParseFlags, EMPTY_PATTERN_WITH_FLAGS2) {
	Flags flags = {0};
	Map map;
	Regex patterns;
	int argc = 3;
	char **argv;
	argv = (char **)malloc(sizeof(char *) * 5);

	argv[0] = (char *)malloc(100);
	argv[1] = (char *)malloc(100);
	argv[2] = (char *)malloc(100);
	argv[3] = (char *)malloc(100);

	strcpy(argv[0], "./s21_grep");
	strcpy(argv[1], "");
	strcpy(argv[2], "-o");
	strcpy(argv[3],"file_name");

	map.mnum = patterns.pnum = 0;
	map.whoiswho = (int*)malloc((argc - 1) * sizeof(int));


	ParseFlags(argc, &argv, &flags, &map, &patterns);
	ASSERT_EQ(patterns.print_opt, 0);

	freeTab(argv);
	free(map.whoiswho);
}

TEST (ParseFlags, PATTERN_WO_EF) {
	Flags flags = {0};
	Map map;
	Regex patterns;
	int argc = 3;
	char **argv;
	argv = (char **)malloc(sizeof(char *) * 5);

	argv[0] = (char *)malloc(100);
	argv[1] = (char *)malloc(100);
	argv[2] = (char *)malloc(100);
	argv[3] = (char *)malloc(100);

	strcpy(argv[0], "./s21_grep");
	strcpy(argv[1], "pattern");
	strcpy(argv[2], "-o");
	strcpy(argv[3],"file_name");

	map.mnum = patterns.pnum = 0;
	map.whoiswho = (int*)malloc((argc - 1) * sizeof(int));


	ParseFlags(argc, &argv, &flags, &map, &patterns);
	ASSERT_EQ(strcmp(patterns.full_pattern, "pattern"), 0);

	freeTab(argv);
	free(map.whoiswho);
	regfree(&patterns.regex);
}

//
//TEST(GREP, COMBO) {
//	std::ifstream file_combo;
//	file_combo.open("test_files/full_coverage_combo.csv");
//	std::string combo;
//
//	int i = 1;
//	while (std::getline(file_combo, combo)) {
//		FILE* s21_grep = popen((std::string("./s21_grep fprintf ") + combo).c_str(), "r");
//		FILE* unx_grep = popen((std::string("grep fprintf ") + combo).c_str(), "r");
//
//		if (!s21_grep || !unx_grep) exit(1);
//		char s21_c = getc(s21_grep);
//		char unx_c = getc(unx_grep);
//		std::cout << "grep test #" << std::setw(3) << i++ << ": " << std::setw(20) << combo.substr(0, combo.find(' ', 0)) << " ...";
//		while (s21_c != EOF || unx_c != EOF) {
//			ASSERT_EQ(s21_c, unx_c);
//			s21_c = getc(s21_grep), unx_c = getc(unx_grep);
//		}
//		std::cout << " done ✅ " << std::endl;
//		pclose(s21_grep);
//		pclose(unx_grep);
//	}
//}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
