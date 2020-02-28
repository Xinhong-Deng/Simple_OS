//
// Created by sandra on 2/16/20.
//

#ifndef ECSE427_PCB_H
#define ECSE427_PCB_H
typedef struct PCB {
    int PC;
    int start;
    int end;
} PCB;

PCB* makePCB(int start, int end);

#endif //ECSE427_PCB_H
