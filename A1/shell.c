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
#include <unistd.h>
#include "interpreter.h"
#include "shell.h"

void printString(char** input, int size);
void skipSpaces(char**);
void printWordArrays(char** input, int inputSize);
void printWord(char*, int);

int main (int argc, char** argv)
{
	printf ("Welcome to the Sandra Deng's shell!\n");
	printf ("Version 1.0 Created January 2020\n");

	while (1) {
        char* commandInput = (char*) malloc(sizeof(char) * 1000);
        char* head = commandInput;

        printf ("$ ");
        fgets(commandInput, 999, stdin);
        if (!isatty(STDIN_FILENO)) {
            // input from tile redirection
            printf("%s", commandInput);
        }

        char* parsedInput[100];
        int sizeOfParsedInput = parseInput(&commandInput, parsedInput);
        free(head);

        int errorCode = interpreter(parsedInput, false, sizeOfParsedInput);
        if (errorCode == -1) {
            exit(EXIT_FAILURE);
        } else if (errorCode == PRINT_ERROR) {
            printf("Variable does not exist\n");
        } else if (errorCode == SCRIPT_NOT_FOUND) {
            printf("Script not found\n");
        } else if (errorCode == SYNTAX_ERROR) {
            printf("Unknown command\n");
        } else if (errorCode == MEMORY_FULL) {
            printf("No space in the shell memory\n");
        } else if (errorCode == QUIT_FROM_SCRIPT) {
            //do nothing, wait for user input
        }

	}
}

int parseInput(char** commandInput,  char** parsedInput) {

	int parsedInputIndex = 0;

	char word[100];
	while (**commandInput != '\0' && parsedInputIndex < 100) {

        //skip the space at the beginning
        skipSpaces(commandInput);

        int wordIndex = 0;
		for (; wordIndex < 100 && **commandInput != ' ' && **commandInput != '\0'
		        && **commandInput != '\r' && **commandInput != '\n'; wordIndex++, (*commandInput)++) {

		    /* keyboard type in ends with '\n\0'
		     * file input ends with '\r\n\0'
		     */

		    word[wordIndex] = **commandInput;
		}

		if (**commandInput == '\r') {
            (*commandInput) ++;
		}

		word[wordIndex] = '\0';
		parsedInput[parsedInputIndex] = strdup(word);

		parsedInputIndex ++;
		(*commandInput) ++;
	}

	return (parsedInputIndex --);
}

void skipSpaces(char** commandInput) {
    while (**commandInput == ' ' && **commandInput != '\n' && **commandInput != '\r') {
        (*commandInput)++;
    }

    return;
}

// debug use only!!!
void printString(char** input, int size) {
    int i = 0;
    for (; i < size; i++) {
        printf ("line %d: %s \n", i, input[i]);
    }
}

void printWordArrays(char** input, int inputSize) {
    for (int i = 0; i < inputSize; i ++) {
        printf("word %d: %s\n", i, input[i]);
		printf("%d\n", input[i][0]);
	}
}

void printWord(char* word, int wordSize) {
    int i = 0;
    for (; i < wordSize; i ++) {
	    printf("%c %d\n", word[i], word[i]);
    }
}
