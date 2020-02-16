//
// Created by sandra on 2/16/20.
//

#include <stdio.h>
#include "kernel.h"
#include "shell.h"
#include "interpreter.h"
#include "ram.h"
#include "shellmemory.h"

int main(int argc, char** argv) {
    shellUI(argc, argv);
    return 0;
}

