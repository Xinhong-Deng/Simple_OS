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
    isCpuBusy = true;
    for (int i = 0; i < quanta; i++) {

        strcpy(cpu->IR, ram[cpu->IP]);
        int errCode = interpret(cpu->IR, true);
        if (errCode < 0) {
            // 0: no error; 1: quit from file
            return errCode;
        }
        free(ram[cpu->IP]);
        cpu->IP ++;
    }
    isCpuBusy = false;
    return 0;
}