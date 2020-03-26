//
// Created by sandra on 2/16/20.
//

#include "cpu.h"
#include <string.h>
#include <stdbool.h>
#include "interpreter.h"
#include "ram.h"
#include "statusCode.h"

int run(int quanta) {
    isCpuBusy = true;
    //todo: should include offset to fetch the instruction
    for (int i = 0; i < quanta; i++) {
        // todo: cannot handle incomplete last page
        if (cpu->offset == 4) {
            isCpuBusy = false;
            return PAGE_FAULT;
        }

        strcpy(cpu->IR, ram[cpu->IP * 4 + cpu->offset]);
        int errCode = interpret(cpu->IR, true);
        if (errCode < 0 || errCode == QUIT_FROM_SCRIPT) {
            // 0: no error; 1: quit from file
            isCpuBusy = false;
            return errCode;
        }

        cpu->offset ++;
    }
    isCpuBusy = false;
    return 0;
}