//
// Created by sandra on 2/16/20.
//

#ifndef ECSE427_CPU_H
#define ECSE427_CPU_H

#include <stdlib.h>
typedef struct CPU {
    int IP;
    char IR[1000];
    int quanta;
} CPU;

CPU* initCPU() {
    CPU* cpu = (CPU*) malloc(sizeof(CPU));
    cpu->quanta = 2;
    return  cpu;
}

CPU* cpu;
int cpuRun(int quanta);
#endif //ECSE427_CPU_H
