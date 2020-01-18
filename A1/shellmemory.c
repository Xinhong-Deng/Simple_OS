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
#include "shellmemory.h"

ShellMem* getElement(char*);

ShellMem* shellMem[100];

void setMem (char* key, char* value) {
	ShellMem* target = getElement(key);


	if (target == NULL) {
		//move it out??
		printf ("no space in the shell memory\n");
		return;
	}

	strcpy(target->value, value);
}

char* getValue (char* key) {
	ShellMem* target = getElement(key);

	return target->value;
}

ShellMem* getElement(char* key) {
	ShellMem* target;
	int i = 0;
	while (i < 100) {
		if (shellMem[i]->key == NULL) {
			target = shellMem[i];
			strcpy (target->key, key);
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
