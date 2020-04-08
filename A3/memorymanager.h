//
// Created by sandra on 3/23/20.
//

#ifndef ASSIGNMENT2_MEMORYMANAGER_H
#define ASSIGNMENT2_MEMORYMANAGER_H
#include <stdlib.h>
#include <stdio.h>
#include "pcb.h"
int launcher(FILE* f);

int countTotalPages(FILE* f);

void loadPage(int pageNumber, FILE* f, int frameNumber);

int findFrame();

int findVictim(PCB* p);

int updatePageTable(PCB *p, int pageNumber, int frameNumber, int victimFrame);

void removePageTable(PCB* p);
#endif //ASSIGNMENT2_MEMORYMANAGER_H
