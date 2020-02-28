//
// Created by sandra on 2/16/20.
//

#ifndef ECSE427_KERNEL_H
#define ECSE427_KERNEL_H

#include "pcb.h"
typedef struct Node {
    PCB* pcb;
    struct Node* next;
}Node;
void addToReadyQueue(PCB* pcb);

Node* head;
Node* tail;

int myinit(const char* fileName);
int scheduler();

#endif //ECSE427_KERNEL_H
