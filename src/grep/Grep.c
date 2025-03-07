#include "s21_grep.h"

static void print4L(Flags* flags, const char* file_name, int mnum) {
	if (flags->c) {
		if (mnum != 1) {
			if (flags->h) {
				fprintf(stdout, "1\n%s\n", file_name);
			}
			else {
				fprintf(stdout, "%s:1\n%s\n", file_name, file_name);
			}
		} 
		else {
			fprintf(stdout, "1\n%s\n", file_name);
		}
	}
	else {
		fprintf(stdout, "%s\n", file_name);
	}
}

static void print4C(Flags* flags, const char* file_name, int mnum, int nmatched) {
	if (mnum != 1) {
		if (flags->h) {
			fprintf(stdout, "%d\n", nmatched);
		}
		else {
			fprintf(stdout, "%s:%d\n", file_name, nmatched);
		}
	} 
	else {
		fprintf(stdout, "%d\n", nmatched);
	}
}

static void printBasic(Flags* flags, char* line, const char* file_name, int mnum, int numLine) {
	if (mnum != 1) {
		if (flags->h) {
			if (flags->n) {
				fprintf(stdout, "%d:%s", numLine, line);
			}
			else {
				fprintf(stdout, "%s", line);
			}
		}
		else {
			if (flags->n) {
				fprintf(stdout, "%s:%d:%s", file_name, numLine, line);
			}
			else {
				fprintf(stdout, "%s:%s", file_name, line);
			}
		}
	}
	else {
		if (flags->n) {
			fprintf(stdout, "%d:%s", numLine, line);
		}
		else {
			fprintf(stdout, "%s", line);
		}
	}
	if (flags->o && !flags->v) {
		fprintf(stdout, "\n");
	}
}

//static void Tree(Regex* patterns, FILE* filep, char* file_name, int mnum, Flags* flags) {
//
//
//		int offset = 0, printed = 0;
//		if (patterns->full) {
//			
//		}
//		
//		while (regexec(&patterns->regex, line + offset, 1, pmatch, 0) == (flags->v ? REG_NOMATCH : 0) && !printed) {
//			if (flags->l) {
//				print4L(flags, file_name, mnum);
//				return ;
//			}
//			if (flags->o) {
//				int start = pmatch[0].rm_so + offset;
//				int end = pmatch[0].rm_eo + offset;
//				char oline[end-start];
//				strncpy(oline, line + start, end-start);
//				printBasic(flags, oline, file_name, mnum, numLine);
//				offset = end;
//				}
//			}
//			else {
//				if ((!flags->o && !flags->c) || (flags->o && flags->v && !flags->c)) {
//					printBasic(flags, line, file_name, mnum, numLine);
//					printed = 1;
//				}
//			}
//			if (flags->c) {
//				++nmatched;
//				break;
//			}
//		}
//	}
//}

static void PrintBasedOnOpt(FILE* filep, const char* file_name, int mnum, Flags* flags, Regex* patterns) {
	regmatch_t pmatch[1];
	int nmatched = 0; 
	size_t numLine = 0;
	size_t bufsize = 32;

	char* line = (char *)malloc(sizeof(char) * bufsize); 
	if (!line) exit(1);

	while (getline(&line, &bufsize, filep) != -1) {
		int offset = 0;
		numLine++;
		if (patterns->print_opt == 2) {
			while (regexec(&patterns->regex, line + offset, 1, pmatch, 0) == (flags->v ? REG_NOMATCH : 0)) {
				if (flags->l) {
					print4L(flags, file_name, mnum);
					return ;
				}
				else if (flags->c) {
					++nmatched;
					break;
				}
				else if (flags->o) {
					int start = pmatch[0].rm_so + offset;
					int end = pmatch[0].rm_eo + offset;
					char oline[end-start];
					strncpy(oline, line + start, end-start);
					printBasic(flags, oline, file_name, mnum, numLine);
					offset = end;
				}
				else  {
					printBasic(flags, line, file_name, mnum, numLine);
					break;
				}
			}
		}
		if (patterns->print_opt == 1) {
			if (flags->l) {
				print4L(flags, file_name, mnum);
			}
			else if (flags->c) {
				++nmatched;
			}
			else {
				printBasic(flags, line, file_name, mnum, numLine);
			}
		}
	}
	if (flags->c) {
		print4C(flags, file_name, mnum, nmatched);
	}
	rewind(filep);
	free(line);
}

void Grep(char*** argv, Flags* flags, Map* map, Regex* patterns) {
	int mnum;
	FILE *filep = NULL;
	char *file_name;

	mnum = (patterns->pnum ? map->mnum : map->mnum - 1);
	for (int i = (patterns->pnum ? 0 : 1); i < map->mnum; ++i) {
		file_name = (*argv)[map->whoiswho[i]];
		filep = fopen(file_name, "r");
		if (!filep) {
			if (!flags->s) {
				fprintf(stdout, "s21_grep: %s: No such file or directory\n", file_name);
			}
			continue;
		}
		PrintBasedOnOpt(filep, file_name, mnum, flags, patterns);
		fclose(filep);
	}
	if (patterns->print_opt == 2) {
		regfree(&patterns->regex);
	}
}
