#include "s21_common.h"

void s21_open_file(FILE** file, char* file_name, char* method) {
	*file = fopen(file_name, method);
	if (!file) { fprintf(stderr, "not opened"); exit(1); }
//	fprintf(stdout, "opened\n");
}
