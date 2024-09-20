#ifndef S21_CAT_H
# define S21_CAT_H
# include <stdbool.h>
# include "../s21_common/s21_common.h" 

# define ERROR_NO_ARGS "Error [s21_cat.c -> main]: The program was launched without arguments\n"
# define ERROR_NO_FLAG "Error [flagsParsing.c]: There is no such flag\n"

typedef struct flags {
	bool rowNumNonblank;
	bool nonPrintingEnd;
	bool rowNum;
	bool squeezeBlank;
	bool nonPrintingTabs;
	bool nonPrinting; 
} flags;

/* Getting Valid Flags */
void ParseFlags(char*** argv, flags* inputInfo);

/*Getting Something Else*/

#endif
