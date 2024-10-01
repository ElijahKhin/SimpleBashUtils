#include <string.h>
#include <iomanip>
#include <gtest/gtest.h>
#include <fstream>
#include "s21_cat.h"

void freeTab(char **tab) {
	for (int i = 0; tab[i] != NULL; ++i)
		free(tab[i]);
	free(tab);
}

TEST(Flags, b) {
	int i = 1;
	char **argv = s21_split("exec -b file", ' ');
	flags inputInfo = {0};

	ParseFlags(3, &i, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.rowNumNonblank, 1);
	EXPECT_EQ(inputInfo.nonPrintingEnd, 0);
	EXPECT_EQ(inputInfo.rowNum, 0);
	EXPECT_EQ(inputInfo.squeezeBlank, 0);
	EXPECT_EQ(inputInfo.nonPrintingTabs, 0);
	EXPECT_EQ(inputInfo.nonPrinting, 0);

	freeTab(argv);
}

TEST(Flags, e) {
	int i = 1;
	char **argv = s21_split("exec -e file", ' ');
	flags inputInfo = {0};

	ParseFlags(3, &i, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.rowNumNonblank, 0);
	EXPECT_EQ(inputInfo.nonPrintingEnd, 1);
	EXPECT_EQ(inputInfo.rowNum, 0);
	EXPECT_EQ(inputInfo.squeezeBlank, 0);
	EXPECT_EQ(inputInfo.nonPrintingTabs, 0);
	EXPECT_EQ(inputInfo.nonPrinting, 1);

	freeTab(argv);
}

TEST(Flags, n) {
	int i = 1;
	char **argv = s21_split("exec -n file", ' ');
	flags inputInfo = {0};

	ParseFlags(3, &i, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.rowNumNonblank, 0);
	EXPECT_EQ(inputInfo.nonPrintingEnd, 0);
	EXPECT_EQ(inputInfo.rowNum, 1);
	EXPECT_EQ(inputInfo.squeezeBlank, 0);
	EXPECT_EQ(inputInfo.nonPrintingTabs, 0);
	EXPECT_EQ(inputInfo.nonPrinting, 0);

	freeTab(argv);
}

TEST(Flags, s) {
	int i = 1;
	char **argv = s21_split("exec -s file", ' ');
	flags inputInfo = {0};

	ParseFlags(3, &i, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.rowNumNonblank, 0);
	EXPECT_EQ(inputInfo.nonPrintingEnd, 0);
	EXPECT_EQ(inputInfo.rowNum, 0);
	EXPECT_EQ(inputInfo.squeezeBlank, 1);
	EXPECT_EQ(inputInfo.nonPrintingTabs, 0);
	EXPECT_EQ(inputInfo.nonPrinting, 0);

	freeTab(argv);
}

TEST(Flags, t) {
	int i = 1;
	char **argv = s21_split("exec -t file", ' ');
	flags inputInfo = {0};

	ParseFlags(3, &i, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.rowNumNonblank, 0);
	EXPECT_EQ(inputInfo.nonPrintingEnd, 0);
	EXPECT_EQ(inputInfo.rowNum, 0);
	EXPECT_EQ(inputInfo.squeezeBlank, 0);
	EXPECT_EQ(inputInfo.nonPrintingTabs, 1);
	EXPECT_EQ(inputInfo.nonPrinting, 1);

	freeTab(argv);
}

TEST(Flags, v) {
	int i = 1;
	char **argv = s21_split("exec -v file", ' ');
	flags inputInfo = {0};

	ParseFlags(3, &i, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.rowNumNonblank, 0);
	EXPECT_EQ(inputInfo.nonPrintingEnd, 0);
	EXPECT_EQ(inputInfo.rowNum, 0);
	EXPECT_EQ(inputInfo.squeezeBlank, 0);
	EXPECT_EQ(inputInfo.nonPrintingTabs, 0);
	EXPECT_EQ(inputInfo.nonPrinting, 1);

	freeTab(argv);
}

TEST(Flags, All) {
	int i = 1;
	char **argv = s21_split("exec -benstv file", ' ');
	flags inputInfo = {0};

	ParseFlags(3, &i, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.rowNumNonblank, 1);
	EXPECT_EQ(inputInfo.nonPrintingEnd, 1);
	EXPECT_EQ(inputInfo.rowNum, 0);
	EXPECT_EQ(inputInfo.squeezeBlank, 1);
	EXPECT_EQ(inputInfo.nonPrintingTabs, 1);
	EXPECT_EQ(inputInfo.nonPrinting, 1);

	freeTab(argv);
}

TEST(Flags, AllWithGNU) {
	int i = 1;
	char **argv = s21_split("exec -benstvTE file", ' ');
	flags inputInfo = {0};

	ParseFlags(3, &i, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.rowNumNonblank, 1);
	EXPECT_EQ(inputInfo.nonPrintingEnd, 1);
	EXPECT_EQ(inputInfo.rowNum, 0);
	EXPECT_EQ(inputInfo.squeezeBlank, 1);
	EXPECT_EQ(inputInfo.nonPrintingTabs, 1);
	EXPECT_EQ(inputInfo.nonPrinting, 1);

	freeTab(argv);
}

TEST(Flags, AllSeparated) {
	int i = 1;
	char **argv = s21_split("exec -b -e -n -s -t -v file", ' ');
	flags inputInfo = {0};

	ParseFlags(8, &i, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.rowNumNonblank, 1);
	EXPECT_EQ(inputInfo.nonPrintingEnd, 1);
	EXPECT_EQ(inputInfo.rowNum, 0);
	EXPECT_EQ(inputInfo.squeezeBlank, 1);
	EXPECT_EQ(inputInfo.nonPrintingTabs, 1);
	EXPECT_EQ(inputInfo.nonPrinting, 1);

	freeTab(argv);
}

TEST(Flags, AllSeparatedWithGNU) {
	int i = 1;
	char **argv = s21_split("exec -b -e -n -s -t -v -T -E file", ' ');
	flags inputInfo = {0};

	ParseFlags(10, &i, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.rowNumNonblank, 1);
	EXPECT_EQ(inputInfo.nonPrintingEnd, 1);
	EXPECT_EQ(inputInfo.rowNum, 0);
	EXPECT_EQ(inputInfo.squeezeBlank, 1);
	EXPECT_EQ(inputInfo.nonPrintingTabs, 1);
	EXPECT_EQ(inputInfo.nonPrinting, 1);

	freeTab(argv);
}

TEST(LongFlags, NumberNonblank) {
	int i = 1;
	char **argv = s21_split("exec --number-nonblank file", ' ');
	flags inputInfo = {0};

	ParseFlags(3, &i, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.rowNumNonblank, 1);
	EXPECT_EQ(inputInfo.nonPrintingEnd, 0);
	EXPECT_EQ(inputInfo.rowNum, 0);
	EXPECT_EQ(inputInfo.squeezeBlank, 0);
	EXPECT_EQ(inputInfo.nonPrintingTabs, 0);
	EXPECT_EQ(inputInfo.nonPrinting, 0);

	freeTab(argv);
}

TEST(LongFlags, Number) {
	int i = 1;
	char **argv = s21_split("exec --number file", ' ');
	flags inputInfo = {0};

	ParseFlags(3, &i, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.rowNumNonblank, 0);
	EXPECT_EQ(inputInfo.nonPrintingEnd, 0);
	EXPECT_EQ(inputInfo.rowNum, 1);
	EXPECT_EQ(inputInfo.squeezeBlank, 0);
	EXPECT_EQ(inputInfo.nonPrintingTabs, 0);
	EXPECT_EQ(inputInfo.nonPrinting, 0);

	freeTab(argv);
}

TEST(LongFlags, Squeeze) {
	int i = 1;
	char **argv = s21_split("exec --squeeze-blank file", ' ');
	flags inputInfo = {0};

	ParseFlags(3, &i, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.rowNumNonblank, 0);
	EXPECT_EQ(inputInfo.nonPrintingEnd, 0);
	EXPECT_EQ(inputInfo.rowNum, 0);
	EXPECT_EQ(inputInfo.squeezeBlank, 1);
	EXPECT_EQ(inputInfo.nonPrintingTabs, 0);
	EXPECT_EQ(inputInfo.nonPrinting, 0);

	freeTab(argv);
}

TEST(LongFlags, All) {
	int i = 1;
	char **argv = s21_split("exec --number-nonblank --number --squeeze-blank file", ' ');
	flags inputInfo = {0};

	ParseFlags(5, &i, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.rowNumNonblank, 1);
	EXPECT_EQ(inputInfo.nonPrintingEnd, 0);
	EXPECT_EQ(inputInfo.rowNum, 0);
	EXPECT_EQ(inputInfo.squeezeBlank, 1);
	EXPECT_EQ(inputInfo.nonPrintingTabs, 0);
	EXPECT_EQ(inputInfo.nonPrinting, 0);

	freeTab(argv);
}

TEST(PairedFlags, BN) {
	int i = 1;
	char **argv = s21_split("exec -bn file", ' ');
	flags inputInfo = {0};

	ParseFlags(3, &i, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.rowNumNonblank, 1);
	EXPECT_EQ(inputInfo.nonPrintingEnd, 0);
	EXPECT_EQ(inputInfo.rowNum, 0);
	EXPECT_EQ(inputInfo.squeezeBlank, 0);
	EXPECT_EQ(inputInfo.nonPrintingTabs, 0);
	EXPECT_EQ(inputInfo.nonPrinting, 0);

	freeTab(argv);
}

TEST(PairedFlags, NB) {
	int i = 1;
	char **argv = s21_split("exec -nb file", ' ');
	flags inputInfo = {0};

	ParseFlags(3, &i, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.rowNumNonblank, 1);
	EXPECT_EQ(inputInfo.nonPrintingEnd, 0);
	EXPECT_EQ(inputInfo.rowNum, 0);
	EXPECT_EQ(inputInfo.squeezeBlank, 0);
	EXPECT_EQ(inputInfo.nonPrintingTabs, 0);
	EXPECT_EQ(inputInfo.nonPrinting, 0);

	freeTab(argv);
}

TEST(ALL_FLAGS, ALL_LONG_AND_SHORT) {
	int i = 1;
	char **argv = s21_split("exec --number-nonblank --number --squeeze-blank -benstvTE file", ' ');
	flags inputInfo = {0};

	ParseFlags(6, &i, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.rowNumNonblank, 1);
	EXPECT_EQ(inputInfo.nonPrintingEnd, 1);
	EXPECT_EQ(inputInfo.rowNum, 0);
	EXPECT_EQ(inputInfo.squeezeBlank, 1);
	EXPECT_EQ(inputInfo.nonPrintingTabs, 1);
	EXPECT_EQ(inputInfo.nonPrinting, 1);

	freeTab(argv);
}

TEST(ALL_FLAGS, ALL_LONG_AND_SHORT_SEP) {
	int i = 1;
	char **argv = s21_split("exec --number-nonblank --number --squeeze-blank -b -e -n -s -t -v -T -E file", ' ');
	flags inputInfo = {0};

	ParseFlags(13, &i, &argv, &inputInfo);

	EXPECT_EQ(inputInfo.rowNumNonblank, 1);
	EXPECT_EQ(inputInfo.nonPrintingEnd, 1);
	EXPECT_EQ(inputInfo.rowNum, 0);
	EXPECT_EQ(inputInfo.squeezeBlank, 1);
	EXPECT_EQ(inputInfo.nonPrintingTabs, 1);
	EXPECT_EQ(inputInfo.nonPrinting, 1);

	freeTab(argv);
}

TEST(CAT, UNX_TESTS) {
	std::ifstream unx_combo;
	unx_combo.open("unx_full_coverage_combo.csv");
	std::string combo;
	char* ps21_cat, punx_cat;

	int i = 1;
	while (std::getline(unx_combo, combo)) {
		FILE* s21_cat = popen((std::string("./s21_cat ") + combo).c_str(), "r");
		FILE* unx_cat = popen((std::string("cat ") + combo).c_str(), "r");

		if (!s21_cat || !unx_cat) exit(1);
		char s21_c = getc(s21_cat);
		char unx_c = getc(unx_cat);
		std::cout << "cat_unix_flags test #" << std::setw(3) << i++ << ": " << std::setw(20) << combo.substr(0, combo.find(' ', 0)) << " ...";
		while (s21_c != EOF && unx_c != EOF) {
			ASSERT_EQ(s21_c, unx_c);
			s21_c = getc(s21_cat), unx_c = getc(unx_cat);
		}
		std::cout << " done ✅ " << std::endl;
		pclose(s21_cat);
		pclose(unx_cat);
	}
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
