//
// Created by sandra on 2/16/20.
//

#include "ram.h"


int currentAvailablePos = 0;

void addToRam(FILE* p, int* start, int* end) {
    *start = currentAvailablePos;
    while (1) {
        char buffer[100];
        fgets(buffer, sizeof(buffer), p);
        if (feof(p)) {
            break;
        }

        //todo: handle ram[] is full??
        ram[currentAvailablePos] = strdup(buffer);
        currentAvailablePos ++;
    }

    *end = currentAvailablePos - 1;

}

void printRam() {
    for (int i = 0; i < currentAvailablePos; i++) {
        printf("debug: ram[%d]: %s", i, ram[i]);
    }
}
