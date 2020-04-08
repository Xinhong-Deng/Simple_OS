#include "interpreter.h"
#include "shellmemory.h"
#include "statusCode.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

int shellUI(int argc, const char *argv[])
{
    printf ("Welcome to the Sandra Deng's shell!\n");
    printf ("Shell version 2.0 Updated February 2020\n");

    shell_memory_initialize();

    while (1) {

        char* commandInput = (char*) malloc(sizeof(char) * 1000);

        printf ("$ ");
        FILE* tty = stdin;
        fgets(commandInput, 999, tty);
        if (feof(tty)) {
            tty = fopen("/dev/tty", "r");
            fgets(commandInput, 999, tty);
        }

        if (!isatty(STDIN_FILENO)) {
            // input from tile redirection
            printf("%s", commandInput);
        }

        // todo: need to add additional error message!!
        int errorCode = interpret(commandInput, false);
        free(commandInput);
        if (errorCode == -1) {
            shell_memory_destory();
            exit(EXIT_FAILURE);
        } else{
            printErrorMessage(errorCode);
        }

    }

}