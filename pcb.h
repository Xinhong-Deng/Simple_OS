//
// Created by sandra on 2/16/20.
//

#include <stdbool.h>

#ifndef ECSE427_PCB_H
#define ECSE427_PCB_H
typedef struct PCB {
    int PC;
    int start;
    int end;
    int pid;
    int pageTable[10];
} PCB;

PCB* makePCB(int start, int end);

bool isInPageTable(PCB* pcb, int pageNumber);

#endif //ECSE427_PCB_H
