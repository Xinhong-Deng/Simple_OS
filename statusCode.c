//
// Created by sandra on 2/27/20.
//
#include "statusCode.h"
void printErrorMessage(int errorCode) {
    if (errorCode == PRINT_ERROR) {
        printf("Error: Variable does not exist\n");
    } else if (errorCode == SCRIPT_NOT_FOUND) {
        printf("Error: Script not found\n");
    } else if (errorCode == SYNTAX_ERROR) {
        printf("Error: Unknown command\n");
    } else if (errorCode == MEMORY_FULL) {
        printf("Error: Unable to set shell memory.\n");
    } else if (errorCode == EXEC_SCRIPT_LOADED) {
        // already printed
    } else if (errorCode == EXEC_TOO_MANY_SCRIPTS) {
        printf("Error: Provide more than 3 scripts\n");
    } else if (errorCode == TOO_MANY_ARGUMENTS) {
        printf("Error: Malformed command\n");
    } else if (errorCode == RAM_IS_FULL) {
       printf("Error: RAM is full\n");
    } else if (errorCode == LAUNCH_FAILED) {
       printf("Error: Failed to launch the script\n");
    }else if (errorCode == QUIT_FROM_SCRIPT) {
        //do nothing, wait for user input
    }
}