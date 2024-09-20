#include "s21_cat.h"

static void printFlags(flags* inputInfo) {
	printf("rows number non blank: %d\n", inputInfo->rowNumNonblank);
	printf("nonPrinting $: %d\n", inputInfo->nonPrintingEnd);
	printf("rows number: %d\n", inputInfo->rowNum);
	printf("squeeze blank rows: %d\n", inputInfo->squeezeBlank);
	printf("nonPrinting Tabs: %d\n", inputInfo->nonPrintingTabs);
	printf("nonPrinting: %d\n", inputInfo->nonPrinting);
}

int main(int argc, char* argv[]) {
	flags inputInfo = {0};

	if (argc == 1) { fprintf(stderr, ERROR_NO_ARGS); exit(1); }
	ParseFlags(&argv, &inputInfo);
	printFlags(&inputInfo);
	return argc;
}
