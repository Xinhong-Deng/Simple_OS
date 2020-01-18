/*
 * shell.c
 *
 *  Created on: Jan 17, 2020
 *      Author: sandra deng
 *   McGill ID: 260770487
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
//#include "shellmemory.h"

int  parseInput(char* commandInput);
void printString(char** input, int size);

int main (int argc, char** argv)
{
	printf ("Welcome to the sandra shell!\n");
	printf ("Version 1.0 Created January 2020\n");

	//TODO: need to input file name as arg?
	while (1) {
		if (argc == 1) {
			char* commandInput = (char*) malloc (sizeof(char) * 1000);

			printf ("$");
			//TODO: CARRIAGE RETURN!!! \r\n, how to deal with it? does it terminate with \r\n or \0??
			fgets (commandInput, 999, stdin);

//			char commandInput[] = "help";

			int errorCode = parseInput(commandInput);
			if (errorCode == -1) {
				exit(EXIT_FAILURE);
			}

		} else {
			//input from file???
		}
	}

	return 0;
}

int parseInput(char* commandInput) {

	char* parsedInput[100];

	while (*commandInput == ' ') {
		commandInput ++;
	}

	int parsedInputIndex = 0;
	while (*commandInput != '\0' && parsedInputIndex < 100) {
		char word[100];
		int wordIndex = 0;
		for (; wordIndex < 100 && *commandInput != ' ' && *commandInput != '\0'; wordIndex++, commandInput ++) {
			word[wordIndex] = *commandInput;
		}

		word[wordIndex] = '\0';
		parsedInput[parsedInputIndex] = strdup(word);

		parsedInputIndex ++;

		if (*commandInput == '\0') {
			break;
		}
		commandInput ++;
	}

	return interpreter (parsedInput);
}

void printString(char** input, int size) {
	int i = 0;
	for (; i < size; i++) {
		printf ("line %d: %s \n", i, input[i]);
	}
}
