/*
 * interpreter.h
 *
 *  Created on: Jan 18, 2020
 *      Author: sandr
 */

#ifndef INTERPRETER_H_
#define INTERPRETER_H_
#define PRINT_ERROR -2
#define SCRIPT_NOT_FOUND -3
#define SYNTAX_ERROR -4
#define QUIT_FROM_SCRIPT 1

#include <stdbool.h>
#include "shellmemory.h"
int interpreter(char**, bool);
void freeShellMemory();


#endif /* INTERPRETER_H_ */
