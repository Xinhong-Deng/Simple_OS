//
// Created by sandra on 2/16/20.
//

#ifndef ECSE427_CPU_H
#define ECSE427_CPU_H

#include <stdlib.h>
#include <stdbool.h>
typedef struct CPU {
    int IP;
    char IR[1000];
    int quanta;
} CPU;

CPU* cpu;
bool isCpuBusy;
int run(int quanta);
#endif //ECSE427_CPU_H
