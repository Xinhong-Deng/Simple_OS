//
// Created by sandra on 2/16/20.
//

#include <stdlib.h>

#include "kernel.h"
#include "shell.h"
#include "ram.h"
#include "cpu.h"
#include "statusCode.h"
#include "memorymanager.h"

//todo: you may need to move the error handling to the main!!
void kernel(int argc, char** argv) {
    cpu = (CPU*) malloc(sizeof(CPU));
    cpu->quanta = 2;
    isCpuBusy = false;
    shellUI(argc, argv);
}

void boot() {
    system("[ -d BackingStore ]&&rm -r BackingStore");
    system("mkdir BackingStore");
}

int main(int argc, char** argv)
{
    boot();
    kernel(argc, argv);
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


PCB* myinit(const FILE* f1)
{

    int start = 0;
    int end = 0;
    //todo: change add to ram!! should be loaded in the launcher()
    int errCode = addToRam(f1, &start, &end);
    if (errCode < 0) {
//        return errCode;
    }
    PCB* pcb = makePCB(start, end);
    addToReadyQueue(pcb);

    return pcb;
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

        //todo: cannot use this method to detect the line left!!
        int lineLeft = currentPCB->end - currentPCB->PC + 1;
        int quanta = min(lineLeft, 2);
        if (run(quanta) != 0) {
            freeReadyQueue();
            resetRam();
            return 1;
        }

        //todo: not update PC, but update the offset!!
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
    resetRam();
    return 0;
}

