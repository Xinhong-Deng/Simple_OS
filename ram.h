//
// Created by sandra on 2/16/20.
//

#ifndef ECSE427_RAM_H
#define ECSE427_RAM_H
#include <string.h>
#include <stdio.h>
char* ram[1000];
int addToRam(FILE* p, int* start, int* end);
void printRam();
#endif //ECSE427_RAM_H
