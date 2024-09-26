#include "s21_cat.h"

static void WhichRowPart(int* row_i, char c, RowPart* row_part) {
	if (!(*row_i) && c == '\n') *row_part = EMPTY;
	else if (!(*row_i) && c != '\n') *row_part = START;
	else if (*row_i && c != '\n') *row_part = MIDDLE;
	else {*row_part = END; *row_i = 0;}
}

static void PrintRowNumber(bool reset) {
	static int row_num = 1;

	if (reset) row_num = 1;
	else fprintf(stdout, "%6d\t", row_num++);
}

static void PrintData(FILE* file, flags* inputInfo) {
	RowPart row_part;
	int squeeze_i = 0;
	int row_i = 0;
	char c = getc(file);

	while (c != EOF) {
		WhichRowPart(&row_i, c, &row_part);
		if (inputInfo->squeezeBlank && row_part == EMPTY) { 
			squeeze_i++;
			c = getc(file); 
			continue; 
		}
		else
			if (row_part == EMPTY && inputInfo->rowNum) PrintRowNumber(0);
		if (row_part == START) {
			if (squeeze_i) {
				if (inputInfo->rowNum) PrintRowNumber(0);
				fprintf(stdout, "\n");
				squeeze_i = 0;
			}
			if (inputInfo->rowNumNonblank || inputInfo->rowNum) PrintRowNumber(0);
		} 

		fprintf(stdout, "%c", c); if (c == '\n') row_i = 0; else row_i++;
		c = getc(file);
	}
	if (squeeze_i) {
		if (inputInfo->rowNum) PrintRowNumber(0);
		fprintf(stdout, "\n");
	}
	PrintRowNumber(1);
}

void FilesProcessing(int argc, int flagIndex, char*** argv, flags* inputInfo) {
	FILE* file = NULL;

	while(flagIndex < argc) {
		s21_open_file(&file, (*argv)[flagIndex++], "r");
		PrintData(file, inputInfo);
		fclose(file);
	}
}
