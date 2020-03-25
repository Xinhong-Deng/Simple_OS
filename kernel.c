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

    //todo: change add to ram!! should be loaded in the launcher()
    PCB* pcb = makePCB();
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

void queuePutFirstToLast(Node* currentNode) {
    if (tail == head) {
        return;
    }
    head = head->next;
    currentNode->next = NULL;
    tail->next = currentNode;
    tail = currentNode;
}

int scheduler()
{
    while (head != NULL)
    {
        while (isCpuBusy) { }
        Node* currentNode = head;
        PCB* currentPCB = currentNode->pcb;
        cpu->IP = currentPCB->PC;
        cpu->offset = currentPCB->PC_offset;

        // todo: should test how many line left!!
        int statusCode = run(cpu->quanta);

        if (statusCode < 0 || statusCode == 1) {
            // error or the script quit
            freeReadyQueue();
            resetRam();
            return 1;
        }

        if (statusCode == 0) {
            // no page fault
            currentPCB->PC_offset = cpu->offset;
            queuePutFirstToLast(currentNode);
            printf("process[%d] not page fault at page[%d] line[%d] with frame[%d]\n", currentPCB->pid, currentPCB->PC_page, currentPCB->PC_offset, currentPCB->PC);
            continue;
        }

        currentPCB->PC_page ++;
        if (currentPCB->PC_page > currentPCB->page_max || statusCode == END_OF_PROCESS) {
            // remove this pcb from the queue, and all its page in the frame
            removePageTable(currentPCB);
            head = head->next;
            free(currentNode);
            continue;
        }

        // page fault
        currentPCB->PC_offset = 0;
        currentPCB->PC = currentPCB->pageTable[currentPCB->PC_page];
        if (currentPCB->PC != -1) {
            // page fault but page is already loaded in the ram
            printf("process[%d] has page[%d] fault but the new page[%d] is loaded at frame[%d]\n",
                    currentPCB->pid,
                    currentPCB->PC_page-1,
                    currentPCB->PC_page,
                    currentPCB->PC);
            queuePutFirstToLast(currentNode);
            continue;
        }

        char bsFileName[50];
        sprintf(bsFileName, "BackingStore/%d.txt", currentPCB->pid);
        FILE* bsFile = fopen(bsFileName, "w");
        int victimFrame = -1;
        int frameNumber = findFrame();
        if (frameNumber != -1) {
            loadPage(currentPCB->PC_page, bsFile, frameNumber);
        } else {
            victimFrame = findVictim(currentPCB);
            loadPage(currentPCB->PC_page, bsFile, victimFrame);
        }

        updatePageTable(currentPCB, currentPCB->PC_page, frameNumber, victimFrame);
        currentPCB->PC = currentPCB->pageTable[currentPCB->PC_page];

        printf("process[%d] has page fault, and the new page[%d] is loaded at [%d], with victim[%d]\n", currentPCB->pid, currentPCB->PC_page, currentPCB->PC, victimFrame);
        queuePutFirstToLast(currentNode);

    }
    resetRam();
    return 0;
}

