#!/bin/bash
gcc -c shell.c interpreter.c shellmemory.c cpu.c pcb.c ram.c statusCode.c kernel.c
gcc -o mykernel shell.o interpreter.o shellmemory.o cpu.o pcb.o ram.o statusCode.o kernel.o
