//
// Created by sandra on 2/16/20.
//

#include "ram.h"
#include "statusCode.h"

void resetRam() {
    for (int i = 0; i < 40; i++) {
        free(ram[i]);
        ram[i] = NULL;
    }
}

// debug only
void printRam() {
    for (int i = 0; i < 40; i++) {
        if (ram[i] == NULL) {
            printf("ram[%d]: null ", i);
            continue;
        }
        printf("debug: ram[%d]: %s", i, ram[i]);
    }
}
