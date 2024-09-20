#include "s21_cat.h"

static void printFlags(flags* inputInfo) {
	printf("rows number non blank: %d\n", inputInfo->rowNumNonblank);
	printf("nonPrinting $: %d\n", inputInfo->nonPrintingEnd);
	printf("rows number: %d\n", inputInfo->rowNum);
	printf("squeeze blank rows: %d\n", inputInfo->squeezeBlank);
	printf("nonPrinting Tabs: %d\n", inputInfo->nonPrintingTabs);
	printf("nonPrinting: %d\n", inputInfo->nonPrinting);
	printf("is system GNU: %d\n", inputInfo->gnuSystem);
}

int main(int argc, char* argv[]) {
	flags inputInfo = {0,0,0,0,0,0,0};

	ParseFlagsInfo(&argv, &inputInfo);
	printFlags(&inputInfo);
	return argc;
}
