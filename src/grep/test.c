#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

///static void CompRegex(Regex* patterns, char* pattern, bool flagi, int idx) {
///	if ( != 0 ) {
///    fprintf(stderr, "Error: invalid regex: %s\n", pattern);
///		exit(1);
///  }
///	else {
///		++patterns->comp;
///	}
///}
///
///int main() {
///	regex_t regex;
///	FILE* file;
///	size_t buffsize = 32;
///	char* line = (char *)malloc(sizeof(char) * buffsize);
///	file = fopen("pat", "r");
///	while(getline(&line, &buffsize, file) != -1) {
///		fprintf(stdout, "here");
///	}
///	int res = regcomp(&regex, "", 0);
///	fprintf(stdout, "%d\n", res);
///}

//int main() {
//	regex_t regex;
//	regmatch_t pmatch[1];
////	char* pattern = "fprintf|dummy";
//	char* pattern = "";
//	char* line = "This is simple line with two patterns: fprintf and dummy";
//	
//	int pat_res = regcomp(&regex, pattern, REG_EXTENDED);
//	fprintf(stdout, "%d\n", pat_res);
//	int res = regexec(&regex, line, 1, pmatch, 0);	
//	fprintf(stdout, "%d\n", res);
//}

int main(int argc, char** argv) {
	for (int i = 0; i < argc; ++i) {
		fprintf(stdout, "%s len: %d\n", argv[i], (int)strlen(argv[i]));	
	}
}
