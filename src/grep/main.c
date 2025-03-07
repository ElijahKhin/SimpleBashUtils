#include "s21_grep.h"

int main(int argc, char* argv[]) {
	Flags flags = {0};
	Map map;
	Regex patterns;

	map.whoiswho = (int*)malloc((argc - 1) * sizeof(int));
	patterns.efidx = (int*)malloc((argc - 1) * 3 * sizeof(int));	
	patterns.pnum = patterns.comp = 0;
	patterns.full_pattern = NULL;
	if (map.whoiswho == NULL || patterns.efidx == NULL) {
		fprintf(stdout, ERROR_MALLOC); 
		return 1;
	}

	if (argc == 1) { fprintf(stderr, ERROR_NO_ARGS); exit(1); }
	ParseFlags(argc, &argv, &flags, &map, &patterns);
	Grep(&argv, &flags, &map, &patterns);

	free(map.whoiswho);
	free(patterns.efidx);
//	if (patterns.full_pattern) {
//		free(patterns.full_pattern);
//	}
}
