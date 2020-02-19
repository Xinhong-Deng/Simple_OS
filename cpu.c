//
// Created by sandra on 2/16/20.
//

#include "cpu.h"
#include <string.h>
#include <stdbool.h>
#include "interpreter.h"
#include "ram.h"
#include "shell.h"

int run(int quanta) {
    for (int i =0; i < quanta; i++) {
        // todo: cannot check end of script?? or it is done by the caller
        //  and provide this info as the quanta

        // todo: IR is ** or *???

        strcpy(cpu->IR, ram[cpu->IP]);
        char* IR = strdup(cpu->IR);
        char* parsedInput[100];
        parseInput(&IR, parsedInput);
        int errCode = interpreter(parsedInput, false, 0);   // don't want to free the IR, so pass 0
        if (errCode != 0) {
            return errCode;
        }
        ram[cpu->IP] = NULL;
        cpu->IP ++;
    }
    return 0;
}