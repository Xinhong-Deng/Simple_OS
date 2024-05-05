# ECSE427 Assignment

Author: Xinhong Deng

Term: Winter 2020

## A1 (2020.1)

Build a shell being able to show the help message. The shell contains shell memory and you can set variables.
You can run script with this shell.

File Created: shell.c, shell.h, shellmemory.c, shellmemory.h, interpreter.c, interpreter.c

Contain a Makefile

## A2 (2020.2.15)

Based on previous work, simulate a single core CPU kernel.

File Created: kernel.c, cpu.c, pcb.c, ram.c

## A3 (2020.3)

- The OS Boot Sequence to create some necessary OS structures
    - Prepare the Backing Store
    - Prepare RAM for paging
- The Memory Manager to handle memory allocation for processes
    - Launcher
        - Loads new programs to the run-time environment
    - PCB Modifications
        - Addition of the page table
    - Page Fault
        - Find page, swap in, select victim, we will not do a swap out
    - Task Switch additions
        - Generate Page Fault and properly assigns addresses
