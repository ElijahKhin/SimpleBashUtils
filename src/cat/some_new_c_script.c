#include <stdio.h>
#include <stdlib.h>

void some_malloc(){
	char *str; 
	str = (char *)malloc(12);
}

int main(void) {
	some_malloc();
}
