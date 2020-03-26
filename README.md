# ECSE427 Assignment

Author: Xinhong Deng

Term: Winter 2020

## A1 (2020.1)

Build a shell being able to show the help message. THe shell contains shell memory and you can set variables.
You can run script with this shell.

File Created: shell.c, shell.h, shellmemory.c, shellmemory.h, interpreter.c, interpreter.c

Contain a Makefile

## A2 (2020.2.15)

Based on previous work, simulate the kernel.

File Created: kernel.c, cpu.c, pcb.c, ram.c

## A3 (2020.3)

when you free(), the memory location is not accessible, but it is not set to NULL!!!
if you want to know whether it is free() or not somewhere else, set it to NULL after you free() it!!
