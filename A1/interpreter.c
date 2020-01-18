/*
 * interpreter.c
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
#include "shellmemory.h"

void help();
void quit();
void set(char*, char*);
void print(char*);

int interpreter(char* parsedWords[]) {
	int errCode = 0;

//	printf ("%s \n", parsedWords[0]);

	if (strcmp(parsedWords[0], "help\0") == 0) { help(); }
	else if (strcmp(parsedWords[0], "quit\0") == 0) { quit(); }
	else if (strcmp(parsedWords[0], "set\0") == 0) {
		if ((sizeof (*parsedWords) / sizeof (**parsedWords)) < 3) {
			printf("missing set parameter\r");
			return -1;
		}

		set(parsedWords[1], parsedWords[2]);
	}
	else if (strcmp(parsedWords[0], "print\0") == 0) { print(parsedWords[1]); }
	else if (strcmp(parsedWords[0], "run\0") == 0) {
		//TODO
		;
	}
	else { printf("Unknown command\n"); }


	return 0;
}

void help() {
	printf("COMMAND \t \t DESCRIPTION\n");
	printf("help \t \t \t display all the commands\n");
	printf("quit \t \t \t Exits / terminated the shell with \"Bye!\" \n");
	printf("set VAR STRING \t \t Assigns a value to shell memory\n");
	printf("print VAR \t \t Display the STRING assigned to VAR\n");
	printf("run SCRIPT.TXT \t \t Executes the file SCRIPT.TXT \n");

}

void quit() {
	exit(EXIT_SUCCESS);
}

void set(char* varName, char* value) {
	setMem(varName, value);
}

void print(char* name) {
	char* value = getValue(name);

	if (value == NULL) {
		printf("Variable does not exist\n");
		return;
	}

	printf("%s\n", value);
}

void run(char* scriptName) {
//	FILE* script = fopen(scriptName, "r");
//	while (script != EOF) {
//
//	}
//	fclose(script);

}


