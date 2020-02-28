//
// Created by sandra on 2/16/20.
//

#include <stdio.h>
#include <stdlib.h>

#include "kernel.h"
#include "shell.h"
#include "ram.h"
#include "cpu.h"
#include "statusCode.h"

int main(int argc, char** argv)
{
    cpu = (CPU*) malloc(sizeof(CPU));
    cpu->quanta = 2;
    isCpuBusy = false;
    shellUI(argc, argv);
    return 0;
}

void addToReadyQueue(PCB* pcb)
{
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->pcb = pcb;
    newNode->next = NULL;
    if (head != NULL)
    {
        tail->next = newNode;
        tail = newNode;
    }
    else
    {
        head = newNode;
        tail = newNode;
    }

}


int myinit(const char* fileName)
{
    FILE* f1 = fopen(fileName, "r");
    if (f1 == NULL)
    {
        return SCRIPT_NOT_FOUND;
    }
    int start = 0;
    int end = 0;
    addToRam(f1, &start, &end);
    PCB* pcb = makePCB(start, end);
    addToReadyQueue(pcb);

    return 0;
}

int min(int a, int b)
{
    if (a > b) {
        return b;
    }
    return a;
}


void freeReadyQueue()
{
    while (head != NULL)
    {
        Node* next = head->next;
        free(head);
        head = next;
    }
}

int scheduler()
{
    while (head != NULL)
    {
        while (isCpuBusy) { }
        Node* currentNode = head;
        PCB* currentPCB = currentNode->pcb;
        cpu->IP = currentPCB->PC;

        int lineLeft = currentPCB->end - currentPCB->PC + 1;
        int quanta = min(lineLeft, 2);
        if (cpuRun(quanta) != 0) {
            freeReadyQueue();
            return 1;
        }

        currentPCB->PC += quanta;
        if (currentPCB->PC == currentPCB->end + 1)
        {
            // check whether the end of script
            head = head->next;
            free(currentNode);
        } else
        {
            if (tail == head) {
                continue;
            }
            head = head->next;
            currentNode->next = NULL;
            tail->next = currentNode;
            tail = currentNode;
        }

    }
    return 0;
}

