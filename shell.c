#include "interpreter.h"
#include "shellmemory.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int shellUI(int argc, const char *argv[])
{
    printf ("Welcome to the Sandra Deng's shell!\n");
    printf ("Shell version 2.0 Updated February 2020\n");

    shell_memory_initialize();

    while (!feof(stdin))
    {
        printf("$ ");
        fflush(stdout);

        char *line = NULL;
        size_t linecap = 0;
        if (getline(&line, &linecap, stdin) == -1)
            break;

        (void)interpret(line);
        free(line);
        printf("line freed\n");
    }

    shell_memory_destory();

    return 0;
}