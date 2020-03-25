//
// Created by sandra on 2/16/20.
//

#ifndef ECSE427_CPU_H
#define ECSE427_CPU_H
#define PAGE_FAULT 10
#define END_OF_PROCESS 11

#include <stdlib.h>
#include <stdbool.h>
typedef struct CPU {
    int IP;
    char IR[1000];
    int quanta;
    int offset;
} CPU;

CPU* cpu;
bool isCpuBusy;
int run(int quanta);
#endif //ECSE427_CPU_H
