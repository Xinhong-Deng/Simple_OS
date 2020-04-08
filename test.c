#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
//	char* input = (char*) malloc(sizeof(char) * 100);
//	fgets(input, 99, stdin);
//
//	printf("isatty?: %d", isatty(STDIN_FILENO));
//
//	if (isatty(STDIN_FILENO)) {
//		printf("from file\n");
//	}
//	printf("%s", input);
//    char set[50];
//    char print[50];
//    sprintf(print, "print y\n");
//    FILE* f = fopen("g2.txt", "w");
//    for (int i = 0; i < 19; i++) {
//        sprintf(set, "set y %d\n", i + 100);
//        fputs(set, f);
//        fputs(print, f);
//    }
//    fputs("quit\n", f);
//    fclose(f);

//    char* buffer = (char*) malloc(sizeof(char)*100);
//    fgets(buffer, 100, stdin);
//    printf("buffer: %s", buffer);
//    free(buffer);

    printf("file test\n");
    FILE* f = fopen("t.txt", "r");
    char buffer[100];
    fgets(buffer, 100, f);
    printf("%s", buffer);

    f = fopen("t.txt", "r");
    fgets(buffer, 100, f);
    printf("%s", buffer);
	return 0;
}
