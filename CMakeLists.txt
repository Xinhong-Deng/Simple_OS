cmake_minimum_required(VERSION 3.14)
project(Assignment2 C)

set(CMAKE_C_STANDARD 99)

add_executable(Assignment2 shell.c interpreter.c shellmemory.c kernel.c pcb.c ram.c cpu.c)