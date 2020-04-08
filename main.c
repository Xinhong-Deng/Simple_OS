//
// Created by sandra on 4/7/20.
//
#include "kernel.h"

int main(int argc, char** argv)
{
    boot();
    kernel(argc, argv);
    return 0;
}

