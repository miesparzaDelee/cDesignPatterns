#include "hello.h"

#include <stdio.h>

void printHelloWorld()
{
    PrintFormated("Hello World!\n");
}

int (*PrintFormated)(const char*, ...) = printf;
