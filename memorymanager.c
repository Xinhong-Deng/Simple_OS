//
// Created by sandra on 3/23/20.
//

#include "memorymanager.h"
#include <unistd.h>
#include "statusCode.h"
#include "kernel.h"
#include <string.h>
#include "ram.h"

int launcher(FILE* f) {
    int totalPages = countTotalPages(f);
    if (totalPages > 10) {
        return 0;
    }

    //create pcb here
    //todo: check error: add the pcb to the ready queue before load anything to the ram
    PCB* pcb = myinit(f);

    char bsFileName[50];
    sprintf(bsFileName, "BackingStore/%d.txt", pcb->pid);
    FILE* bsFile = fopen(bsFileName, "w");
    char temp[100];
    rewind(f);
    while (fgets(temp, 100, f) != NULL) {
        fputs(temp, bsFile);
    }

    fclose(f);
    fclose(bsFile);

    bsFile = fopen(bsFileName, "r");
    // find the min
    int loadPages = 2;
    if (loadPages > totalPages) {
        loadPages = totalPages;
    }

    for (int i = 0; i < loadPages; i++) {
        int victimFrame = -1;
        int frameNumber = findFrame();
        if (frameNumber != -1) {
            loadPage(i, bsFile, frameNumber);
        } else {
            victimFrame = findVictim(pcb);
            loadPage(i, bsFile, victimFrame);
        }

        updatePageTable(pcb, i, frameNumber, victimFrame);
    }

    return 1;
}

int countTotalPages(FILE* f) {
    char temp[100];
    int count = 0;
    //todo: may have loaded an empty line!!
    while (fgets(temp, 100, f) != NULL) {
        count ++;
    }

    if (count % 4 != 0) {
        return count / 4 + 1;
    }
    return count / 4;
}

void loadPage(int pageNumber, FILE* f, int frameNumber) {
    printf("load page %d into frame %d", pageNumber, frameNumber);
    char* instructions[40];
    char line[100];
    int i = 0;
    while(fgets(line, 100, f) != NULL) {
        instructions[i] = strdup(line);
    }

    for (int x =0; x < 4; x++) {
        ram[frameNumber * 4 + x] = strdup(instructions[pageNumber * 4 + x]);
    }

    printRam();
}

int findFrame() {
    for (int i = 0; i < 10; i ++) {
        if (ram[i*4] == NULL) {
            return i;
        }
    }
    return -1;
}

int findVictim(PCB* p) {
    int victimFrame = rand() % 10;
    if (!isInPageTable(p, victimFrame)) {
        return victimFrame;
    }

    for (int i = victimFrame; i % 10 < 10; i ++) {
        // must be able to terminate, since all scripts have max 10 pages!
        if (!isInPageTable(p, i)) {
            return i;
        }
    }
}

PCB* locateVictim(int victimFrame) {
    Node* currentNode = head;
    while (currentNode != tail) {
        if (isInPageTable(currentNode->pcb, victimFrame)) {
            return currentNode->pcb;
        }
        currentNode = currentNode->next;
    }

    // todo: debug only!! should not happen!! handle this error!!!
    return NULL;
}

int updatePageTable(PCB *p, int pageNumber, int frameNumber, int victimFrame) {
    // if no victim, then the victim frame == -1, frameNumber > -1
    // if has victim, then the victimFrame > -1, frameNumber == -1

    if (victimFrame == -1) {
        p->pageTable[pageNumber] = frameNumber;
        return 0;
    }

    //have victim, update the both the victimPcb and the p
    p->pageTable[pageNumber] = victimFrame;

    PCB* victimPcb = locateVictim(victimFrame);
    if (victimPcb == NULL) {
        // todo: debug only!!
        printf("error!!! victim pcb does not exist\n");
        exit(-1);
    }
    for (int i = 0; i < 10; i ++) {
        if (victimPcb->pageTable[i] == victimFrame) {
            victimPcb->pageTable[i] = -1;
        }
    }

    return 0;
}

