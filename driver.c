// Standard Library Imports
#include <stdio.h>
#include <stdlib.h>

// Algorithms
#include "GenerateData.c"

// Macros
#define PAUSE() system("PAUSE")

int main()
{
    int testArr[50];
    int i;

    GenerateData(testArr, 50);

    for(i = 0; i < 50; i++)
        printf("[%d] %d\n", i+1, testArr[i]);

    PAUSE();

    return 0;
}