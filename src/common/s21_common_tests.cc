#include <string.h>
#include <gtest/gtest.h>

#include "s21_common.h"

TEST(s21_atoi, all_tests) {
	char escape[] = {9, 10, 11, 12, 13, 0};
	std::string e(escape);

	EXPECT_EQ(s21_atoi((e + "1").c_str()), 1);
	EXPECT_EQ(s21_atoi((e + "a1").c_str()), 0);
	EXPECT_EQ(s21_atoi((e + "--1").c_str()), 0);
	EXPECT_EQ(s21_atoi((e + "++1").c_str()), 0);
	EXPECT_EQ(s21_atoi((e + "+1").c_str()), 1);
	EXPECT_EQ(s21_atoi((e + "-1").c_str()), -1);
	EXPECT_EQ(s21_atoi((e + "0").c_str()), 0);
	EXPECT_EQ(s21_atoi((e + "+42lyon").c_str()), 42);
	EXPECT_EQ(s21_atoi((e + "+101").c_str()), 101);
	EXPECT_EQ(s21_atoi((e + std::to_string(MAX_INT)).c_str()), MAX_INT);
	EXPECT_EQ(s21_atoi((e + std::to_string(MIN_INT)).c_str()), MIN_INT);
	EXPECT_EQ(s21_atoi("+-42"), 0);
	EXPECT_EQ(s21_atoi("-+42"), 0);
	EXPECT_EQ(s21_atoi((std::string("+") + e + std::to_string(MIN_INT)).c_str()), 0);
	EXPECT_EQ(s21_atoi((std::string("-") + e + std::to_string(MIN_INT)).c_str()), 0);
	EXPECT_EQ(s21_atoi((std::string("1") + e + std::to_string(MIN_INT)).c_str()), 1);
	EXPECT_EQ(s21_atoi((std::string("-1") + e + std::to_string(MIN_INT)).c_str()), -1);
}

TEST(s21_isdigit, all_tests) {
	EXPECT_EQ(s21_isdigit('0' - 1), 0);
	EXPECT_EQ(s21_isdigit('0'), 1);
	EXPECT_EQ(s21_isdigit('9' + 1), 0);
	EXPECT_EQ(s21_isdigit('9'), 1);
}

TEST(s21_itoa, all_tests) {
	char *test_itoa;  

	test_itoa = s21_itoa(MAX_INT);
	EXPECT_EQ(strcmp(test_itoa, std::to_string(MAX_INT).c_str()), 0);
	free(test_itoa);

	test_itoa = s21_itoa(MIN_INT);
	EXPECT_EQ(strcmp(test_itoa,std::to_string(MIN_INT).c_str()), 0);
	free(test_itoa);

	test_itoa = s21_itoa(0);
	EXPECT_EQ(strcmp(test_itoa,std::to_string(0).c_str()), 0);
	free(test_itoa);

	test_itoa = s21_itoa(1);
	EXPECT_EQ(strcmp(test_itoa,std::to_string(1).c_str()), 0);
	free(test_itoa);

	test_itoa = s21_itoa(-1);
	EXPECT_EQ(strcmp(test_itoa,std::to_string(-1).c_str()), 0);
	free(test_itoa);

	test_itoa = s21_itoa(21);
	EXPECT_EQ(strcmp(test_itoa, std::to_string(21).c_str()), 0);
	free(test_itoa);
}

void freeTab(char **tab) {
	for (int i = 0; tab[i] != NULL; ++i)
		free(tab[i]);
	free(tab);
}

TEST(s21_split, all_tests) {
	char **tab = s21_split("  ElijahKhin  21  ", ' ');

	EXPECT_EQ(strcmp(tab[0], "ElijahKhin"), 0);
	EXPECT_EQ(strcmp(tab[1], "21"), 0);
	EXPECT_EQ(tab[2] == NULL, 1);
	freeTab(tab);

	tab = s21_split("ElijahKhin", 0);
	EXPECT_EQ(strcmp(tab[0], "ElijahKhin"), 0);
	EXPECT_EQ(tab[1] == NULL, 1);
	freeTab(tab);

	tab = s21_split("     ", ' ');
	EXPECT_EQ(tab[0] == NULL, 1);
	freeTab(tab);

	char * invalidReadCheck = new char; *invalidReadCheck = 0;
	tab = s21_split(invalidReadCheck, 0);
	EXPECT_EQ(tab[0] == NULL, 1); delete invalidReadCheck;
	free(tab);

	tab = s21_split("ElijahKhin", ' ');
	EXPECT_EQ(strcmp(tab[0], "ElijahKhin"), 0);
	EXPECT_EQ(tab[1] == NULL, 1);
	freeTab(tab);

	tab = s21_split("", ' ');
	EXPECT_EQ(tab[0] == NULL, 1);
	freeTab(tab);

	char * splitme = strdup("ElijahKhin");
	tab = s21_split(splitme, ' ');
	EXPECT_EQ(strcmp(tab[0], "ElijahKhin"), 0);
	EXPECT_EQ(tab[1] == NULL, 1);
	free(splitme); freeTab(tab);

	splitme = strdup("ElijahKhin ");
	tab = s21_split(splitme, ' ');
	EXPECT_EQ(strcmp(tab[0], "ElijahKhin"), 0);
	EXPECT_EQ(tab[1] == NULL, 1);
	free(splitme); freeTab(tab);

	splitme = strdup(" ElijahKhin");
	tab = s21_split(splitme, ' ');
	EXPECT_EQ(strcmp(tab[0], "ElijahKhin"), 0);
	EXPECT_EQ(tab[1] == NULL, 1);
	free(splitme); freeTab(tab);

	splitme = strdup(" ElijahKhin ");
	tab = s21_split(splitme, ' ');
	EXPECT_EQ(strcmp(tab[0], "ElijahKhin"), 0);
	EXPECT_EQ(tab[1] == NULL, 1);
	free(splitme); freeTab(tab);

	splitme = strdup("--1-2--3---4----5-----21");
	tab = s21_split(splitme, '-');
	EXPECT_EQ(strcmp(tab[0], "1"), 0);
	EXPECT_EQ(strcmp(tab[1], "2"), 0);
	EXPECT_EQ(strcmp(tab[2], "3"), 0);
	EXPECT_EQ(strcmp(tab[3], "4"), 0);
	EXPECT_EQ(strcmp(tab[4], "5"), 0);
	EXPECT_EQ(strcmp(tab[5], "21"), 0);
	EXPECT_EQ(tab[6] == NULL, 1);
	free(splitme); freeTab(tab);
}

TEST(s21_strlen, all_tests) {
	EXPECT_EQ(s21_strlen("school21"), 8);
	EXPECT_EQ(s21_strlen(""), 0);
}

TEST(s21_strlcpy, all_tests) {
	char src[] = "coucou";
	char dest[10]; memset(dest, 'A', 10);

	EXPECT_EQ(s21_strlcpy(dest, src, 0) == strlen(src) && dest[0] == 'A', 1);
	EXPECT_EQ(s21_strlcpy(dest, src, 1) == strlen(src) && dest[0] == 0 && dest[1] == 'A', 1);
	EXPECT_EQ(s21_strlcpy(dest, src, 2) == strlen(src) && dest[0] == 'c' && dest[1] == 0 && dest[2] == 'A', 1);
	EXPECT_EQ(s21_strlcpy(dest, src, -1) == strlen(src) && !strcmp(src, dest) && dest[strlen(src) + 1] == 'A', 1); memset(dest, 'A', 10);
	EXPECT_EQ(s21_strlcpy(dest, src, 6) == strlen(src) && !memcmp(src, dest, 5) && dest[5] == 0, 1); memset(dest, 'A', 10);
	EXPECT_EQ(s21_strlcpy(dest, src, 7) == strlen(src) && !memcmp(src, dest, 7), 1); memset(dest, 'A', 10);
	EXPECT_EQ(s21_strlcpy(dest, src, 8) == strlen(src) && !memcmp(src, dest, 7), 1); memset(dest, 'A', 10);
	EXPECT_EQ(s21_strlcpy(dest, "", 42) == 0 && !memcmp("", dest, 1), 1); memset(dest, 0, 10);
	EXPECT_EQ(s21_strlcpy(dest, "1", 0) == 1 && dest[0] == 0, 1); memset(dest, 'A', 10);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
