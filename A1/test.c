#include <stdio.h>
#include <string.h>

int main(void) {
	char temp[] = "help";
	printf("compare: %d", strcmp(temp, "help\0"));
	return 0;

}
