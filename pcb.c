//
// Created by sandra on 2/16/20.
//

#include "pcb.h"
#include <stdlib.h>

#include <stdio.h>

PCB* makePCB() {
    PCB* pcb = (PCB*) malloc(sizeof(PCB));

    pcb->pid = rand();
    pcb->PC = 0;
    pcb->PC_page = 0;
    pcb->PC_offset = 0;
    pcb->PC_page = 0;

    for (int i = 0; i < 10; i ++) {
        pcb->pageTable[i] = -1;
    }

    return pcb;
}

bool isInPageTable(PCB* pcb, int frameNumber) {
    for (int i = 0; i < 10; i ++) {
        if (pcb->pageTable[i] == frameNumber) {
            return true;
        }
    }
    return false;
}

void printPageTable(PCB* pcb) {
    printf("----- pagetable[%d] -----\n", pcb->pid);
    for (int i = 0; i < 10; i++) {
        printf("[%d]_[%d]\n", i, pcb->pageTable[i]);
    }
}
