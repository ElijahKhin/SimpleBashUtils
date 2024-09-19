#include "s21_cat.h"

static void CheckFlags(char* flag, bool isFlagRequested[7]) {
	for (int i = 1; flag[i]; i++) {
		if (flag[i] == 'b') isFlagRequested[0] = 1; 
		else if (flag[i] == 'e') isFlagRequested[1] = isFlagRequested[5] = 1;
		else if (flag[i] == 'n') isFlagRequested[2] = 1;
		else if (flag[i] == 's') isFlagRequested[3] = 1;
		else if (flag[i] == 't') isFlagRequested[4] = isFlagRequested[5] = 1;
		else if (flag[i] == 'v') isFlagRequested[5] = 1;
		else exit(1);
	}
}

static void CheckGNUflags(char* flag, bool isFlagRequested[7]) {
	if (!strcmp(flag, "--number-nonblank")) isFlagRequested[0] = 1; 
	else if (!strcmp(flag, "--number")) isFlagRequested[2] = 1; 
	else if (!strcmp(flag, "--squeeze-blank")) isFlagRequested[3] = 1; 
	else if (!strcmp(flag, "-T")) {
		isFlagRequested[5] = 1; 
		isFlagRequested[6] = 0;
	}
	else if (!strcmp(flag, "-E")) {
		isFlagRequested[1] = 1;
		isFlagRequested[6] = 0;
	}
	else exit(1);
}

static bool isGNUflag(char c) {
	if (c == '-' || c == 'T' || c == 'E') return 1;
	return 0;
}

static void ParseFlags(char* flag, bool isFlagRequested[7], bool gnuSystem) {
	if (isGNUflag(flag[1]) && gnuSystem) CheckGNUflags(flag, isFlagRequested);
	else if (!isGNUflag(flag[1]) && !gnuSystem) CheckFlags(flag, isFlagRequested);
	else exit(1);
}

void ExcludeIncompatibleFlags(bool isFlagRequested[7]) {
	if (isFlagRequested[0] == 1 && isFlagRequested[2] == 1) 
		isFlagRequested[2] = 0;
}

int main(int argc, char* argv[]) {
	/*
	[0] - b or --number-nonblank
	[1] - e and -v or -E and exclude -v
	[2] - n or --number
	[3] - s or --squeeze-blank
	[4] - t and -v or -T and exclude -v
	[5] - v 
	[6] - include v or exclude if -T or -E
	*/
	 
// Надо ввести жесткое разделение на Linux и Unix
// Вывести все функции для парсинга флагов в отдельный модуль
// Прописать тесты под все возможные комбинации флагов


	bool isFlagRequested[7] = {0,0,0,0,0,0,1};
	bool gnuSystem;

	if (argv[1][0] == '-') gnuSystem = isGNUflag(argv[1][1]);
	int i = 1;
	for(; argv[i][0] == '-'; i++)
		ParseFlags(argv[i], isFlagRequested, gnuSystem);
	ExcludeIncompatibleFlags(isFlagRequested);
		

	printf("%s\n", argv[0]);
	for (int i = 0; i < 6; i++)
		printf("%d\n", isFlagRequested[i]);
	return argc;
}
