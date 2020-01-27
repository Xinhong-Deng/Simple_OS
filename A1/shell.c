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
#include <stdbool.h>
#include "interpreter.h"
#include "shell.h"

void printString(char** input, int size);
void skipSpaces(char**);

int main (void)
{
	printf ("Welcome to the Sandra Deng's shell!\n");
	printf ("Version 1.0 Created January 2020\n");

	while (1) {
        char* commandInput = (char*) malloc (sizeof(char) * 1000);

        printf ("$ ");
        //TODO: CARRIAGE RETURN!!! \r\n, how to deal with it? does it terminate with \r\n or \0??
        fgets (commandInput, 999, stdin);

        char* parsedInput[100];
        parseInput(&commandInput, parsedInput);

        int errorCode = interpreter(parsedInput, false);
        if (errorCode == -1) {
            exit(EXIT_FAILURE);
        }

	}
}

void parseInput(char** commandInput,  char** parsedInput) {

	int parsedInputIndex = 0;

	char word[100];
	while (**commandInput != '\0' && parsedInputIndex < 100) {

        //skip the space at the beginning
        skipSpaces(commandInput);

        int wordIndex = 0;
		for (; wordIndex < 100 && **commandInput != ' ' && **commandInput != '\0'
		        && **commandInput != '\n'; wordIndex++, (*commandInput)++) {
		    word[wordIndex] = **commandInput;
		}

		word[wordIndex] = '\0';
		parsedInput[parsedInputIndex] = strdup(word);

		parsedInputIndex ++;
		(*commandInput) ++;
	}


//	for (int i = 0; i < parsedInputIndex; i ++) {
//        printf("word %d: %s\n", i, parsedInput[i]);
//		printf("%d\n", parsedInput[i][0]);
//	}
}

void printString(char** input, int size) {
	int i = 0;
	for (; i < size; i++) {
		printf ("line %d: %s \n", i, input[i]);
	}
}

void skipSpaces(char** commandInput) {
    while (**commandInput == ' ' && **commandInput != '\n' && **commandInput != '\r') {
        (*commandInput)++;
    }

    return;
}
