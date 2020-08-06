// Standard Library Imports
#include <stdio.h>
#include <stdlib.h>

// Algorithms
#include "GenerateData.c"
#include "bubble.c"

// Macros
#define DATA_LEN 2500

void printArrayData(int * arr, int size)
{
    int i;
    for(i = 0; i < size; i++)
        printf("[%d] %d\n", i, arr[i]);
}

int * createArrCopy(int * arr, int size)
{
    int i;
    int * copy = malloc(size * sizeof(int));
    for(i = 0; i < size; i++)
    {
        copy[i] = arr[i];
    }
    return copy;
}

int main()
{
    int dataSize;
    int * testArr;
    int * dataCopy;
    int counter;
    int i;
    char cChoice;

    printf("Enter n: ");
    scanf("%d", &dataSize);
    testArr = malloc(dataSize * sizeof(int));

    GenerateData(testArr, dataSize);

    printf("Data Generated. Print sample data? [y/N]: ");
    scanf(" %c", &cChoice);
    if(cChoice == 'y' || cChoice == 'Y')
    {
        printf("Sample Data:\n");
        printArrayData(testArr, dataSize);
    }

    // Bubble Sort Testing
    dataCopy = createArrCopy(testArr, dataSize);
    counter = bubbleSort(dataCopy, dataSize);
    printf("\n===== BUBBLE SORT =====\n");
    printf("Print sorted array? [y/N]: ");
    scanf(" %c", &cChoice);
    if(cChoice == 'y' || cChoice == 'Y')
    {
        printf("Sorted Array Elements:\n");
        printArrayData(dataCopy, dataSize);
    }
    printf("\nCounter: %d\n", counter);
    printf("Time Elapsed: %d\n", 0);
    counter = 0;
    free(dataCopy);

    system("PAUSE");

    free(testArr);
    return 0;
}