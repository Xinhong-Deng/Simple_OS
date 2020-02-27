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
        fgets(commandInput, 999, stdin);
        if (!isatty(STDIN_FILENO)) {
            // input from tile redirection
            printf("%s", commandInput);
        }

        int errorCode = interpret(commandInput, false);
        free(commandInput);
//        printf("debug: freed commandInput\n");
        if (errorCode == -1) {
            exit(EXIT_FAILURE);
        } else if (errorCode == PRINT_ERROR) {
            printf("Variable does not exist\n");
        } else if (errorCode == SCRIPT_NOT_FOUND) {
            printf("Script not found\n");
        } else if (errorCode == SYNTAX_ERROR) {
            printf("Unknown command\n");
        } else if (errorCode == MEMORY_FULL) {
            printf("Unable to set shell memory.\n");
        } else if (errorCode == EXEC_SCRIPT_LOADED) {
            printf("Error: Script already loaded \n");
        } else if (errorCode == QUIT_FROM_SCRIPT) {
            //do nothing, wait for user input
        }

    }

    shell_memory_destory();

    return 0;
}