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
	files flagsInfo;
	flagsInfo.idxPatternFiles = (int*)malloc((12) * sizeof(int));
	flags inputInfo = {0};


	ParseFlags(8, &argv, &inputInfo, &flagsInfo);

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
	files flagsInfo;
	flagsInfo.idxPatternFiles = (int*)malloc((12) * sizeof(int));
	flags inputInfo = {0};


	ParseFlags(13, &argv, &inputInfo, &flagsInfo);

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

TEST(GREP, COMBO) {
	std::ifstream file_combo;
	file_combo.open("full_coverage_combo.csv");
	std::string combo;

	int i = 1;
	while (std::getline(file_combo, combo)) {
		FILE* s21_grep = popen((std::string("./s21_grep fprintf ") + combo).c_str(), "r");
		FILE* unx_grep = popen((std::string("grep fprintf ") + combo).c_str(), "r");

		if (!s21_grep || !unx_grep) exit(1);
		char s21_c = getc(s21_grep);
		char unx_c = getc(unx_grep);
		std::cout << "grep test #" << std::setw(3) << i++ << ": " << std::setw(20) << combo.substr(0, combo.find(' ', 0)) << " ...";
		while (s21_c != EOF && unx_c != EOF) {
			ASSERT_EQ(s21_c, unx_c);
			s21_c = getc(s21_grep), unx_c = getc(unx_grep);
		}
		std::cout << " done ✅ " << std::endl;
		pclose(s21_grep);
		pclose(unx_grep);
	}
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
