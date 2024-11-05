#ifdef __cplusplus
extern "C" {
#endif
	#ifndef S21_GREP_H
	# define S21_GREP_H
	# include <stdbool.h>
	# include "../s21_common/s21_common.h" 
	
	# define ERROR_NO_ARGS "Error [s21_grep.c -> main]: The program was launched without arguments\n"
	# define ERROR_NO_FLAG "s21_grep: illegal option -- "
	# define ERROR_MALLOC "s21_grep: wrong memory allocation"
	# define ERROR_NO_FILE "s21_grep: no any file name\n"
	# define USAGE "usage: s21_grep [-eivcln] [file ...]\n"
	# define ERROR_STDIN "s21_grep: stdin request is not supported in this version of cat\n"
	
	typedef struct flagsInfo {
		bool e_pattern;
		bool i_ignore_case;
		bool v_invert;
		bool c_count;
		bool l_files_matched;
		bool n_line_number; 
		bool h_no_file_name;
		bool s_no_messages;
		bool f_file_with_patterns;
		bool o_only_matching;
	} flags;

	typedef struct filesInfo {
		int numFiles;
		int* idxPatternFiles;
	} files;
	

	/* Getting Valid Flags */
	void ParseFlags(int argc, char*** argv, flags* flagsInfo, files* filesInfo);
	void Grep(char*** argv, flags* flagsInfo, files* filesInfo);
	
	/*Getting Something Else*/
	
	#endif
#ifdef __cplusplus
}
#endif
