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
int quit(bool);
void set(char*, char*);
int print(char*);
int run(char*);

int interpreter(char** parsedWords, bool isFromScript) {
	int errCode = 0;

	if (strcmp(parsedWords[0], "help") == 0) { help(); }
	else if (strcmp(parsedWords[0], "quit") == 0) { errCode = quit(isFromScript); }
	else if (strcmp(parsedWords[0], "set") == 0) { set(parsedWords[1], parsedWords[2]); }
	else if (strcmp(parsedWords[0], "print") == 0) { errCode = print(parsedWords[1]); }
	else if (strcmp(parsedWords[0], "run") == 0) { errCode = run(parsedWords[1]); }
	else if (strcmp(parsedWords[0], "") == 0) { }
	else { errCode = SYNTAX_ERROR; }

	free(*parsedWords);
	return errCode;
}

void help() {
	printf("COMMAND \t \t DESCRIPTION\n");
	printf("help \t \t \t Display all the commands\n");
	printf("quit \t \t \t Exits / terminated the shell with \"Bye!\" \n");
	printf("set VAR STRING \t \t Assigns a value to shell memory\n");
	printf("print VAR \t \t Display the STRING assigned to VAR\n");
	printf("run SCRIPT.TXT \t \t Executes the file SCRIPT.TXT \n");
}

int quit(bool isFromScript) {
    printf("Bye!\n");

    if (!isFromScript) {
        freeShellMemory();
        exit(EXIT_SUCCESS);
        return 0;
    } else {
        return QUIT_FROM_SCRIPT;
    }
}

void set(char* varName, char* value) {
	setMem(varName, value);
}

int print(char* name) {
	char* value = getValue(name);

	if (value == NULL) {
		return PRINT_ERROR;
	}

	printf("%s\n", value);
	return 0;
}

int run(char* scriptName) {
	FILE* scriptP = fopen(scriptName, "r");
	if (scriptP == NULL) {
		return SCRIPT_NOT_FOUND;
	}

	char** commands[100];		//accept script with 100 lines of command
	int commandsIndex = 0;
	while (!feof(scriptP)) {

		if (commandsIndex > 100) {
			//TODO: exception handle??
			break;
		}

		char* line = (char*) malloc(sizeof (char) * 1000);
		fgets(line, 999, scriptP);

		while (*line != '\0' && commandsIndex < 100) {
			//no need to read the next file input
			char** command = (char**) malloc(sizeof(char*) * 100);

			//parse each line
			parseInput(&line, command);

			commands[commandsIndex] = command;
			commandsIndex ++;
		}

	}
	fclose(scriptP);

	//execute commands in the file one by one
	int i = 0;
	while (i < commandsIndex) {
		int errCode = interpreter(commands[i], true);
		if (errCode != 0) {
		    //terminate the execution when there is an error
			return errCode;
		}

		i ++;
	}

	return 0;
}


