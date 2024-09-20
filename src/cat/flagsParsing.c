#include "s21_cat.h"

void CheckFlags(char* flag, flags* inputInfo) {
	for (int i = 1; flag[i]; i++) {
		if (flag[i] == 'b') inputInfo->rowNumNonblank = 1; 
		else if (flag[i] == 'e') 
			inputInfo->nonPrintingEnd = inputInfo->nonPrinting = 1;
		else if (flag[i] == 'n') inputInfo->rowNum = 1;
		else if (flag[i] == 's') inputInfo->squeezeBlank = 1;
		else if (flag[i] == 't') 
			inputInfo->nonPrintingTabs = inputInfo->nonPrinting = 1;
		else if (flag[i] == 'v') inputInfo->nonPrinting = 1;
		else exit(1);
	}
}

void CheckGNUflags(char* flag, flags* inputInfo) {
	if (!strcmp(flag, "--number-nonblank")) inputInfo->rowNumNonblank = 1;
	else if (!strcmp(flag, "--number")) inputInfo->rowNum = 1;
	else if (!strcmp(flag, "--squeeze-blank")) inputInfo->squeezeBlank = 1;
	else if (!strcmp(flag, "-T")) inputInfo->nonPrintingTabs = 1;
	else if (!strcmp(flag, "-E")) inputInfo->nonPrintingEnd = 1;
	else exit(1);
}

bool isGNUflag(char c) {
	if (c == '-' || c == 'T' || c == 'E') return 1; 
	return 0;
}

void GetFlags(char* flag, flags* inputInfo) {
	if (isGNUflag(flag[1]) && inputInfo->gnuSystem) 
		CheckGNUflags(flag, inputInfo);
	else if (!isGNUflag(flag[1]) && !inputInfo->gnuSystem) 
		CheckFlags(flag, inputInfo);
	else exit(1);
}

void ExcludeIncompatibleFlags(flags* inputInfo) {
	if (inputInfo->rowNumNonblank == 1 && inputInfo->rowNum == 1) 
		inputInfo->rowNum = 0;
}

void whichSystem(char c, flags* inputInfo) {
	inputInfo->gnuSystem = isGNUflag(c);
}

void ParseFlagsInfo(char*** argv, flags* inputInfo) {
	whichSystem((*argv)[1][1], inputInfo);
	int i = 1;
	for(; (*argv)[i][0] == '-'; i++)
		GetFlags((*argv)[i], inputInfo);
	ExcludeIncompatibleFlags(inputInfo);
}
