//
// Created by sandra on 2/16/20.
//

#include <stdbool.h>

#ifndef ECSE427_PCB_H
#define ECSE427_PCB_H
typedef struct PCB {
    int PC;
    int PC_offset;
    int PC_page;
    int page_max;
    int pid;
    int pageTable[10];
} PCB;

PCB* makePCB();

bool isInPageTable(PCB* pcb, int pageNumber);

void printPageTable(PCB* pcb);

#endif //ECSE427_PCB_H
