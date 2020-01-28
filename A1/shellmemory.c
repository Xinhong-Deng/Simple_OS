/*
 * shellmemory.c
 *
 *  Created on: Jan 17, 2020
 *      Author: sandra deng
 *   McGill ID: 260770487
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "shellmemory.h"

ShellMem* getElement(char*, bool);

ShellMem* shellMem[100];

int memSize = 0;

int setMem(char* key, char* value) {
	ShellMem* target = getElement(key, true);

	if (target == NULL) {
		return MEMORY_FULL;
	}

	target->value = strdup(value);
	return 0;
}

char* getValue(char* key) {
	ShellMem* target = getElement(key, false);

	if (target == NULL) {
		return NULL;
	}

	return target->value;
}

ShellMem* getElement(char* key, bool isCreateNewElement) {
	ShellMem* target = NULL;

	int i = 0;
	while (i < 100) {
		if (shellMem[i] == NULL) {
			if (isCreateNewElement) {
				shellMem[i] = (ShellMem*) malloc(sizeof (ShellMem));
				memSize ++;
				target = shellMem[i];
				target->key = strdup(key);
			}
			break;
		}

		if (strcmp(shellMem[i]->key, key) == 0) {
			target = shellMem[i];
			break;
		}

		i++;
	}

	return target;
}

void freeShellMemory() {
    int i = 0;
    for (; i < memSize; i++) {
        free(shellMem[i]);
    }
    memSize = 0;
}