#ifdef __cplusplus
extern "C" {
#endif
	#ifndef S21_GREP_H
	# define S21_GREP_H
	# include <stdbool.h>
	# include <regex.h>
	# include "../s21_common/s21_common.h" 
	
	# define ERROR_NO_ARGS "Error [s21_grep.c -> main]: The program was launched without arguments\n"
	# define ERROR_NO_FLAG "s21_grep: illegal option -- "
	# define ERROR_MALLOC "s21_grep: wrong memory allocation"
	# define ERROR_NO_FILE "s21_grep: no any file name\n"
	# define USAGE "usage: s21_grep [-eivcln] [file ...]\n"
	# define ERROR_STDIN "s21_grep: stdin request is not supported in this version of cat\n"
	
	typedef struct {
		bool i;
		bool v;
		bool c;
		bool l;
		bool n; 
		bool h;
		bool s;
		bool o;
	} Flags;

	typedef struct {
		int mnum;
		int* whoiswho;
	} Map;

	typedef struct {
		int file_emp;
		int patt_emp;
		int comp;
		int pnum;
		int print_opt;
		int* efidx;
		char* full_pattern;
		regex_t regex;
	} Regex;
	

	/* Getting Valid Flags */

	void Alloc4E(int* len, char* pattern, Regex* patterns);
	void Alloc4F(int* len, char* file_name, Regex* patterns);
	bool AllocFullPattern(char*** argv, Regex* patterns);
	void GetPrintOption(bool alloc_res, Regex* patterns, Flags* flags);
	void ConcatPattern(char*** argv, Regex* patterns);

	void PreparePatterns4Parsing(int argc, char*** argv, Regex* patterns, int* i, int j);
	void GetFlagInfo(int argc, char*** argv, int* i, Flags* flags, Regex* patterns);
	void ParseFlags(int argc, char*** argv, Flags* flagsInfo, Map* filesInfo, Regex* patterns);
	void Grep(char*** argv, Flags* flags, Map* map, Regex* patterns);
	
	/*Getting Something Else*/
	
	#endif
#ifdef __cplusplus
}
#endif
