//
// Created by sandra on 2/16/20.
//

#include "ram.h"
#include "statusCode.h"


int currentAvailablePos = 0;

int addToRam(FILE* p, int* start, int* end) {
    *start = currentAvailablePos;
    while (1) {
        char *buffer = NULL;
        size_t buffercap = 0;
        getline(&buffer, &buffercap, p);
        if (feof(p)) {
            break;
        }

        if (currentAvailablePos >= 1000) {
            return RAM_IS_FULL;
        }
        ram[currentAvailablePos] = strdup(buffer);
        currentAvailablePos ++;
    }

    *end = currentAvailablePos - 1;
    return 0;
}

void resetRam() {
    currentAvailablePos = 0;
}

// debug only
void printRam() {
    for (int i = 0; i < 40; i++) {
        printf("debug: ram[%d]: %s", i, ram[i]);
    }
}
