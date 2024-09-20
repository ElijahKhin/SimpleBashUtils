#ifndef S21_CAT_H
# define S21_CAT_H
# include <stdbool.h>
# include "../s21_common/s21_common.h" 

typedef struct flags {
	bool rowNumNonblank;
	bool nonPrintingEnd;
	bool rowNum;
	bool squeezeBlank;
	bool nonPrintingTabs;
	bool nonPrinting; 
	bool gnuSystem;
} flags;

/* Getting Valid Flags */
void CheckFlags(char* flag, flags* inputInfo);
void CheckGNUflags(char* flag, flags* inputInfo);
bool isGNUflag(char c);
void GetFlags(char* flag, flags* inputInfo);
void ExcludeIncompatibleFlags(flags* inputInfo);
void whichSystem(char c, flags* inputInfo);
void ParseFlagsInfo(char*** argv, flags* inputInfo);

/*Getting Something Else*/


#endif
