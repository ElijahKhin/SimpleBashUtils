#ifdef __cplusplus
extern "C" {
#endif
	#ifndef S21_CAT_H
	# define S21_CAT_H
	# include <stdbool.h>
	# include "../s21_common/s21_common.h" 
	
	# define ERROR_NO_ARGS "Error [s21_cat.c -> main]: The program was launched without arguments\n"
	# define ERROR_NO_FLAG "s21_cat: illegal option -- "
	# define ERROR_NO_FILE "s21_cat: no any file name\n"
	# define USAGE "usage: s21_cat [-benstv] [file ...]\n"
	# define ERROR_STDIN "s21_cat: stdio request is not supported in this version of cat\n"
	
	typedef struct flags {
		bool rowNumNonblank;
		bool nonPrintingEnd;
		bool rowNum;
		bool squeezeBlank;
		bool nonPrintingTabs;
		bool nonPrinting; 
	} flags;

	typedef enum SpecifyPartOfPart { EMPTY, START, MIDDLE, END } RowPart;

	
	/* Getting Valid Flags */
	void ParseFlags(int argc, int* flagIndex, char*** argv, flags* inputInfo);
	void FilesProcessing(int argc, int flagIndex, char*** argv, flags* inputInfo);
	
	/*Getting Something Else*/
	
	#endif
#ifdef __cplusplus
}
#endif
