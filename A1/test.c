#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char* input = (char*) malloc(sizeof(char) * 100);
	fgets(input, 99, stdin);

	printf("isatty?: %d", isatty(STDIN_FILENO));

	if (isatty(STDIN_FILENO)) {
		printf("from file\n");
	}
	printf("%s", input);
	return 0;
}
