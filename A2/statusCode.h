//
// Created by sandra on 2/26/20.
//

#ifndef ASSIGNMENT2_STATUSCODE_H
#define ASSIGNMENT2_STATUSCODE_H
#define PRINT_ERROR -2
#define SCRIPT_NOT_FOUND -3
#define SYNTAX_ERROR -4
#define MEMORY_FULL -5
#define EXEC_SCRIPT_LOADED -6
#define EXEC_TOO_MANY_SCRIPTS -7
#define TOO_MANY_ARGUMENTS -8
#define RAM_IS_FULL -9
#define QUIT_FROM_SCRIPT 1

#include <stdlib.h>
#include <stdio.h>
void printErrorMessage(int errorCode);

#endif //ASSIGNMENT2_STATUSCODE_H
