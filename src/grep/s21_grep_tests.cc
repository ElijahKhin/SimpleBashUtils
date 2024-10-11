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

TEST(Flags, all) {
	char **argv = s21_split("exec -e -i  dummy.c -v file_name file_name -clnhsfo", ' ');
	int *idxPatternFiles = (int*)malloc((7) * sizeof(int));
	flags inputInfo = {0};


	ParseFlags(8, idxPatternFiles, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.e_pattern, 1); 
	EXPECT_EQ(inputInfo.i_ignore_case, 1);
	EXPECT_EQ(inputInfo.v_invert, 1);
	EXPECT_EQ(inputInfo.c_count, 1);
	EXPECT_EQ(inputInfo.l_files_matched, 1);
	EXPECT_EQ(inputInfo.n_line_number, 1);
	EXPECT_EQ(inputInfo.h_no_file_name, 1);
	EXPECT_EQ(inputInfo.s_no_messages, 1);
	EXPECT_EQ(inputInfo.f_file_with_patterns, 1);
	EXPECT_EQ(inputInfo.o_only_matching, 1);

	freeTab(argv);
}

TEST(Flags, AllSeparated) {
	char **argv = s21_split("exec -e -i -v file -c -l -n -h -s file_name -f -o", ' ');
	int *idxPatternFiles = (int*)malloc((12) * sizeof(int));
	flags inputInfo = {0};


	ParseFlags(13, idxPatternFiles, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.e_pattern, 1); 
	EXPECT_EQ(inputInfo.i_ignore_case, 1);
	EXPECT_EQ(inputInfo.v_invert, 1);
	EXPECT_EQ(inputInfo.c_count, 1);
	EXPECT_EQ(inputInfo.l_files_matched, 1);
	EXPECT_EQ(inputInfo.n_line_number, 1);
	EXPECT_EQ(inputInfo.h_no_file_name, 1);
	EXPECT_EQ(inputInfo.s_no_messages, 1);
	EXPECT_EQ(inputInfo.f_file_with_patterns, 1);
	EXPECT_EQ(inputInfo.o_only_matching, 1);

	freeTab(argv);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
