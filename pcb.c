//
// Created by sandra on 2/16/20.
//

#include "pcb.h"
#include <stdlib.h>
#include <time.h>

PCB* makePCB(int start, int end) {
    PCB* pcb = (PCB*) malloc(sizeof(PCB));
    pcb->PC = start;
    pcb->start = start;
    pcb->end = end;
    srand(time(NULL));
    pcb->pid = rand();
    return pcb;
}

bool isInPageTable(PCB* pcb, int pageNumber) {

}
