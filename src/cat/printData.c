#include "s21_cat.h"

static void WhichRowPart(int* row_i, char c, RowPart* row_part) {
	if (!(*row_i) && c == '\n') *row_part = EMPTY;
	else if (!(*row_i) && c != '\n') *row_part = START;
	else if (*row_i && c != '\n') *row_part = MIDDLE;
	else {*row_part = END; *row_i = 0;}
}

static void PrintRowNumber(int* row_num) {
	fprintf(stdout, "%6d\t", (*row_num)++);
}

static int SqueezeIfEmpty(bool isFlagSqueeze, RowPart row_part, int* squeeze_i) {
	if (isFlagSqueeze && row_part == EMPTY) {(*squeeze_i)++; return 1;}
	return 0;
}

static void PrintRowNumForBlankIfNotSqueeze(flags* inputInfo, RowPart row_part, int* row_num) {
	if (inputInfo->rowNum && row_part == EMPTY) PrintRowNumber(row_num);
	if (inputInfo->nonPrintingEnd && row_part == EMPTY) fprintf(stdout, "$");
}

static void PrintRowNumAfterSeriaOfEmplyLines(flags* inputInfo, int* squeeze_i, int* row_num) {
	if (inputInfo->rowNum) PrintRowNumber(row_num);
	if (inputInfo->nonPrintingEnd) {
		if (inputInfo->rowNumNonblank) fprintf(stdout, "%6c\t", ' ');
		fprintf(stdout, "$");
	}
	fprintf(stdout, "\n");
	(*squeeze_i) = 0;
}

static void CheckIfNewLine(char c, int* row_i, bool isFlagNonPrintingEnd) {
	if (c == '\n') {
		(*row_i) = 0; 
		if (isFlagNonPrintingEnd) fprintf(stdout, "$");
	}
	else (*row_i)++;
}

static void ProcessLastSeriaOfEmptyLines(flags* inputInfo, int* row_num) {
	if (inputInfo->rowNum) PrintRowNumber(row_num);
	if (inputInfo->nonPrintingEnd) {
		if (inputInfo->rowNumNonblank) fprintf(stdout, "%6c\t", ' ');
		fprintf(stdout, "$");
	}
	fprintf(stdout, "\n");
}

static void CheckIfTab(bool isFlagTabs, char* c) {
	if (isFlagTabs && *c == '\t') {
		fprintf(stdout, "^");
		*c = 'I';
	}
}

//static void PrintChar(bool isFlagNonPrinting, char c) {
//	if (isFlagNonPrinting) {
//		if (c < 32 && c != 9 && c != 10)
//
//	}
//}

static void PrintData(FILE* file, flags* inputInfo) {
	RowPart row_part;
	int row_num = 1;
	int squeeze_i = 0;
	int row_i = 0;
	char c = getc(file);

	while (c != EOF) {
		WhichRowPart(&row_i, c, &row_part);
		if (SqueezeIfEmpty(inputInfo->squeezeBlank, row_part, &squeeze_i)) {
			c = getc(file); 
			continue;
		}
		else PrintRowNumForBlankIfNotSqueeze(inputInfo, row_part, &row_num);
		if (row_part == START && squeeze_i) 
			PrintRowNumAfterSeriaOfEmplyLines(inputInfo, &squeeze_i, &row_num);
		if (row_part == START && (inputInfo->rowNumNonblank || inputInfo->rowNum)) {
			PrintRowNumber(&row_num);
		}
		
		CheckIfNewLine(c, &row_i, inputInfo->nonPrintingEnd);
		CheckIfTab(inputInfo->nonPrintingTabs, &c);
		fprintf(stdout, "%c", c);
//		PrintChar(inputInfo->nonPrinting, c); 
		c = getc(file);
	}
	if (squeeze_i) ProcessLastSeriaOfEmptyLines(inputInfo, &row_num);
}

void FilesProcessing(int argc, int flagIndex, char*** argv, flags* inputInfo) {
	FILE* file = NULL;

	while(flagIndex < argc) {
		s21_open_file(&file, (*argv)[flagIndex++], "r");
		PrintData(file, inputInfo);
		fclose(file);
	}
}
