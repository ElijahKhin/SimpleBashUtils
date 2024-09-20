#include "s21_cat.h"

static bool isLongFlag(char c) {
	return (c == '-'); 
}

static void GetShortFlag(char* flag, flags* inputInfo) {
	for (int i = 1; flag[i]; i++) {
		if (flag[i] == 'b') inputInfo->rowNumNonblank = 1; 
		else if (flag[i] == 'e') 
			inputInfo->nonPrintingEnd = inputInfo->nonPrinting = 1;
		else if (flag[i] == 'E') inputInfo->nonPrintingEnd = 1;
		else if (flag[i] == 'n') inputInfo->rowNum = 1;
		else if (flag[i] == 's') inputInfo->squeezeBlank = 1;
		else if (flag[i] == 't') 
			inputInfo->nonPrintingTabs = inputInfo->nonPrinting = 1;
		else if (flag[i] == 'T') inputInfo->nonPrintingTabs = 1;
		else if (flag[i] == 'v') inputInfo->nonPrinting = 1;
		else { fprintf(stderr, ERROR_NO_FLAG); exit(1); };
	}
}

static void GetLongFlag(char* flag, flags* inputInfo) {
	if (!strcmp(flag, "--number-nonblank")) inputInfo->rowNumNonblank = 1;
	else if (!strcmp(flag, "--number")) inputInfo->rowNum = 1;
	else if (!strcmp(flag, "--squeeze-blank")) inputInfo->squeezeBlank = 1;
	else { fprintf(stderr, ERROR_NO_FLAG); exit(1); };
}


static void GetFlags(char* flag, flags* inputInfo) {
	if (isLongFlag(flag[1])) GetLongFlag(flag, inputInfo);
	else GetShortFlag(flag, inputInfo);
}

static void ExcludeIncompatibleFlags(flags* inputInfo) {
	if (inputInfo->rowNumNonblank == 1 && inputInfo->rowNum == 1) 
		inputInfo->rowNum = 0;
}

void ParseFlags(char*** argv, flags* inputInfo) {
	int i = 1;
	for(; (*argv)[i][0] == '-'; i++)
		GetFlags((*argv)[i], inputInfo);
	ExcludeIncompatibleFlags(inputInfo);
}
