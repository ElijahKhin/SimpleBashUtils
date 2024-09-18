#include "s21_cat.h"

bool ParseFlags(char* flag) {
	bool isFlag[6] = {0,0,0,0,0,0};
// во флаге слово. Может быть такое: -fa -vb -sb 
	for (int i = 1; flag[i]; i++) {
		if (flag[i] == 'b') isFlag[0] = 1;
		if (flag[i] == 'e') isFlag[1] = isFlag[5] = 1;
		if (flag[i] == 'n') isFlag[2] = 1;
		if (flag[i] == 's') isFlag[3] = 1;
		if (flag[i] == 't') isFlag[4] = isFlag[5] = 1;
	}
	return isFlag[0];
}

int main(int argc, char* argv[]) {
	bool isFlag;	
	int i = 1;
	for(; argv[i][0] == '-'; i++) {
			ParseFlags(argv[i]);
	}
		

	printf("%s\n", argv[0]);
	return argc;
}
