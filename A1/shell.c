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
#include "shell.h"

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

			char* parsedInput[100];
			parseInput(&commandInput, parsedInput);

			int errorCode = interpreter (parsedInput);
			if (errorCode == -1) {
				exit(EXIT_FAILURE);
			}

		} else {
			//input from file???
		}
	}

	return 0;
}

void parseInput(char** commandInput,  char** parsedInput) {

	while (**commandInput == ' ') {
		(*commandInput)++;
	}

	int parsedInputIndex = 0;

	char word[100];
	while (**commandInput != '\0' && **commandInput != '\n' && parsedInputIndex < 100) {

		int wordIndex = 0;
		for (; wordIndex < 100 && **commandInput != ' ' && **commandInput != '\0' && **commandInput != '\n'; wordIndex++, (*commandInput)++) {
			word[wordIndex] = **commandInput;
		}

		word[wordIndex] = '\0';
		parsedInput[parsedInputIndex] = strdup(word);

		parsedInputIndex ++;
		(*commandInput) ++;
	}

	for (int i = 0; i < parsedInputIndex; i ++) {
		printf("%d\n", parsedInput[i][0]);
	}
}

void printString(char** input, int size) {
	int i = 0;
	for (; i < size; i++) {
		printf ("line %d: %s \n", i, input[i]);
	}
}
