#include <stdio.h>

char *add(int, int);

typedef char* (* FuncPoint)(int, int);

int main(int argc, char **argv) {
	FuncPoint fp;
	fp = add;

	return 0;
}

char *add(int n1, int n2) {
	char *str;

	return str;
}

