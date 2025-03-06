#include "s21_grep.h"

static void trimNewline(char *line) {
  size_t len = strlen(line);
  if (len > 0 && line[len - 1] == '\n') {
    line[len - 1] = '\0';
  }
}

static void CompRegex(Regex* patterns,  bool flagi) {
	if (regcomp(&(patterns->regex), patterns->full_pattern, (flagi ? (REG_EXTENDED | REG_ICASE) : REG_EXTENDED)) != 0 ) {
    fprintf(stderr, "Error: invalid regex: %s\n", patterns->full_pattern);
		exit(1);
  }
}

void Alloc4E(int* len, char* pattern, Regex* patterns) {
	int llen = strlen(pattern);
	if (llen) {
		*len += llen + 1;
	}
	else {
		patterns->patt_emp = 1;
	}
}

void Alloc4F(int* len, char* file_name, Regex* patterns) {
	size_t bufsize = 32;
	FILE* filep = NULL;
	char* line = (char *)malloc(sizeof(char) * bufsize);
	if (!line) exit(1);
	s21_open_file(&filep, file_name, "r");
	char c = fgetc(filep);
	if (c == EOF) {
		patterns->file_emp = 1;
		free(line);
		return ;
	}
	rewind(filep);
	while (getline(&line, &bufsize, filep) != -1) {
		int llen = strlen(line);
		if (llen == 1 && line[llen - 1] == '\n') {
			patterns->patt_emp = 1;
			break;
		}
		if (llen > 0) {
			*len += llen;
		}
	}
	free(line);
}

bool AllocFullPattern(char*** argv, Regex* patterns) {
	patterns->file_emp = patterns->patt_emp = 0;
	int len = 0;
	for (int i = 0; i < patterns->pnum; i += 3) {
		if (patterns->efidx[i] == 'e') {
			Alloc4E(&len, (*argv)[patterns->efidx[i + 2]] + patterns->efidx[i+1], patterns);
		}
		else {
			Alloc4F(&len, (*argv)[patterns->efidx[i + 2]] + patterns->efidx[i+1], patterns);
		}
	}
	if (len) {
		patterns->full_pattern = (char *)malloc(sizeof(char) * (len + 1));
		if (!patterns->full_pattern) {
			exit(1);
		}
		return 1;
	}
	else {
		return 0;
	}
}

void GetPrintOption(bool alloc_res, Regex* patterns, Flags* flags) {
	if (patterns->patt_emp && (flags->v || flags->o)) {
		patterns->print_opt = 0;
		return ;
	}
	if (patterns->patt_emp) {
		patterns->print_opt = 1;
		return ;
	}
	if (patterns->file_emp && flags->v) {
		if (!alloc_res) patterns->print_opt = 1;
		else patterns->print_opt = 2;
		return ;
	}
	if (patterns->file_emp) {
		patterns->print_opt = 0;
		return ;
	}
	patterns->print_opt = 2;
}


void ConcatPattern(char*** argv, Regex* patterns) {
	for (int i = 0, j = 0; i < patterns->pnum; i += 3) {
		if (patterns->efidx[i] == 'e') {
			if (j > 0)
				strcat(patterns->full_pattern, "|");
			strcat(patterns->full_pattern, (*argv)[patterns->efidx[i + 2]] + patterns->efidx[i+1]);
			++j;
		}
		else {
			size_t bufsize = 32;
			FILE* filep = NULL;
			// where is null check?
			char* line = (char *)malloc(sizeof(char) * bufsize); 
			if (!line) exit(1);
			s21_open_file(&filep, (*argv)[patterns->efidx[i + 2]] + patterns->efidx[i+1], "r");
			while (getline(&line, &bufsize, filep) != -1) {
				trimNewline(line);
				if (j > 0 || patterns->full_pattern[0])
					strcat(patterns->full_pattern, "|");
				strcat(patterns->full_pattern, line);
				++j;
			}
			free(line);
		}
	}
}

void PreparePatterns4Parsing(int argc, char*** argv, Regex* patterns, int* i, int j) {
	patterns->efidx[patterns->pnum++] = (*argv)[*i][j]; // e || f
	if ((*argv)[*i][j+1]) {
		patterns->efidx[patterns->pnum++] = ++j; // j if current else 0 - if pattern in next arg
		patterns->efidx[patterns->pnum++] = *i; // current arg or next
	}
	else {
		if (*i + 1 >= argc) {
			fprintf(stderr, "s21_grep: option requires an argument -- %c\n", (*argv)[*i][j]);
			exit(1);
		}
		patterns->efidx[patterns->pnum++] = 0; // j if current else 0 - if pattern in next arg
		patterns->efidx[patterns->pnum++] = ++(*i); // current arg or next
	}
}

void GetFlagInfo(int argc, char*** argv, int* i, Flags* flags, Regex* patterns) {
	for (int j = 1; (*argv)[*i][j]; ++j) {
		if ((*argv)[*i][j] == 'e' || (*argv)[*i][j] == 'f') {
			PreparePatterns4Parsing(argc, argv, patterns, i, j);
			return ;
		}
		else if ((*argv)[*i][j] == 'i') flags->i = 1;
		else if ((*argv)[*i][j] == 'v') flags->v = 1;
		else if ((*argv)[*i][j] == 'c') flags->c = 1;
		else if ((*argv)[*i][j] == 'l') flags->l = 1;
		else if ((*argv)[*i][j] == 'n') flags->n = 1;
		else if ((*argv)[*i][j] == 'h') flags->h = 1;
		else if ((*argv)[*i][j] == 's') flags->s = 1;
		else if ((*argv)[*i][j] == 'o') flags->o = 1;
		else { fprintf(stderr, "%s%c\n%s", ERROR_NO_FLAG, (*argv)[*i][j], USAGE); exit(1);}
	}
}

static void DropUselessFlags(Flags* flags) {
	if (flags->l) {
		flags->n = flags->h = flags->o = 0;
	}
	if (flags->c) {
		flags->n = flags->o = 0;
	}
	if (flags->v) {
		flags->o = 0;
	}
}
 
static void ProcessRegexPatterns(char*** argv, Regex* patterns, Flags* flags) {
	bool alloc_res = AllocFullPattern(argv, patterns);
	GetPrintOption(alloc_res, patterns, flags);
	if (alloc_res && patterns->print_opt == 2)
		ConcatPattern(argv, patterns);
}

static void ProcessBasicEmptyPattern(Regex* patterns, Flags* flags) {
	if (flags->v || flags->o) 
		patterns->print_opt = 0;
	else 
		patterns->print_opt = 1;
}

//static void ProcessFlagsAndMap() {
//
//}

void ParseFlags(int argc, char*** argv, Flags* flags, Map* map, Regex* patterns) {
	int mnum = 0;
	for(int i = 1; i < argc; i++) {
		if ((*argv)[i][0] == '-' && !(strlen((*argv)[i]) == 1)) { 			
			GetFlagInfo(argc, argv, &i, flags, patterns);
		}
		else {
			map->whoiswho[mnum++] = i;
		}
	}
	DropUselessFlags(flags);
	if (!map->whoiswho[0]) {
		fprintf(stderr, ERROR_NO_FILE), exit(1); 
	}
	map->mnum = mnum;
	if (patterns->pnum)
		ProcessRegexPatterns(argv, patterns, flags);
	else if (!strlen((*argv)[map->whoiswho[0]])) {
		ProcessBasicEmptyPattern(patterns, flags);
		return ;
	}
	else {
		patterns->full_pattern = (*argv)[map->whoiswho[0]];
		patterns->print_opt = 2;
	}
	if (patterns->print_opt == 2) 
		CompRegex(patterns, flags->i);
}
