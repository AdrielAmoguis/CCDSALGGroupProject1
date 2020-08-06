/*
    CCDSALG PROJECT 1 DRIVER EXECUTABLE
    Authors (S14): Amoguis, Sun, Palmares

    Summary:
        This driver file iterates through all the sorting algorithms
        with randomized values each iteration and records all the MET
        and TFC data into a text file named "testLog.txt" after each
        algortihm runs. File writing is in append mode.
*/

// Standard Library Imports
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Algorithms
#include "GenerateData.c"
#include "bubble.c"
//#include "insertion.c"
//#include "selection.c"
//#include "merge.c"
//#include "algo5.c"
//#include "algo6.c"

// Macros
#define DATA_LEN 2500

// Struct
typedef struct
{
    // Algorithm Name
    char algoName[31];
    // Sample Size
    int sampleSize;
    // MET
    double machineExecutionTime;
    // Frequency Count
    long unsigned int count;
} DataLog;

void generateLog(DataLog data)
{
    FILE *fp = fopen("testLog.txt", "a");
    time_t t;
    time(&t);
    fprintf(fp, "===== %s =====\n", data.algoName);
    fprintf(fp, "Sample Size: %d\n", data.sampleSize);
    fprintf(fp, "MET: %lf\n", data.machineExecutionTime);
    fprintf(fp, "TFC: %ld\n", data.count);
    fprintf(fp, "Tested on: %s\n", ctime(&t));
    fprintf(fp, "==========\n");
    fclose(fp);
}

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
    bool isAFK = true, doLogging = false;
    int nRuns, programRun, dataSize;
    int * testArr;
    int * dataCopy;
    unsigned long long counter;
    int i;
    char cChoice;
    struct timespec begin, end;
    int seconds;
    long long unsigned int nanoseconds;
    double timeElapsed;
    DataLog log;

    printf("Run for how many times? : ");
    scanf("%d", &nRuns);
    printf("Turn on automated mode? [Y/n]: ");
    scanf(" %c", &cChoice);
    if(cChoice == 'n' || cChoice == 'N')
        isAFK = false;
    printf("Log results? [y/N]: ");
    scanf(" %c", &cChoice);
    if(cChoice == 'y' || cChoice == 'Y')
        doLogging = true;
    printf("=============================\n");

    for(programRun = 0; programRun < nRuns; programRun++)
    {
        printf("Program Iteration M = %d of %d\n\n", programRun+1, nRuns);
        printf("Enter n: ");
        scanf("%d", &dataSize);
        testArr = malloc(dataSize * sizeof(int));
        log.sampleSize = dataSize;

        GenerateData(testArr, dataSize);

        if(!isAFK)
        {
            printf("Data Generated. Print sample data? [y/N]: ");
            scanf(" %c", &cChoice);
            if(cChoice == 'y' || cChoice == 'Y')
            {
                printf("Sample Data:\n");
                printArrayData(testArr, dataSize);
            }
        }

        // Bubble Sort Testing
        dataCopy = createArrCopy(testArr, dataSize);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
        printf("\n===== BUBBLE SORT START =====\n");
        counter = bubbleSort(dataCopy, dataSize);
        printf("\n===== BUBBLE SORT END =====\n");
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
        if(!isAFK)
        {
            printf("Print sorted array? [y/N]: ");
            scanf(" %c", &cChoice);
            if(cChoice == 'y' || cChoice == 'Y')
            {
                printf("Sorted Array Elements:\n");
                printArrayData(dataCopy, dataSize);
            }
        }
        printf("\nCounter: %d\n", counter);
        seconds = end.tv_sec - begin.tv_sec;
        nanoseconds = end.tv_nsec - begin.tv_nsec;
        timeElapsed = seconds + nanoseconds*1e-9;
        printf("Machine Execution Time: %lf seconds (%lf miliseconds)\n", timeElapsed, timeElapsed * 1000);
        if(doLogging)
        {
            strcpy(log.algoName, "BUBBLE SORT");
            log.count = counter;
            log.machineExecutionTime = timeElapsed;
            generateLog(log);
        }
        counter = 0;
        free(dataCopy);

        /*
        // Insertion Sort Testing
        dataCopy = createArrCopy(testArr, dataSize);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
        printf("\n===== INSERTION SORT START =====\n");
        //counter = bubbleSort(dataCopy, dataSize);         CALL INSERTION SORT HERE
        printf("\n===== INSERTION SORT END =====\n");
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
        if(!isAFK)
        {
            printf("Print sorted array? [y/N]: ");
            scanf(" %c", &cChoice);
            if(cChoice == 'y' || cChoice == 'Y')
            {
                printf("Sorted Array Elements:\n");
                printArrayData(dataCopy, dataSize);
            }
        }
        printf("\nCounter: %d\n", counter);
        seconds = end.tv_sec - begin.tv_sec;
        nanoseconds = end.tv_nsec - begin.tv_nsec;
        timeElapsed = seconds + nanoseconds*1e-9;
        printf("Machine Execution Time: %lf seconds (%lf miliseconds)\n", timeElapsed, timeElapsed * 1000);
        if(doLogging)
        {
            strcpy(log.algoName, "INSERTION SORT");
            log.count = counter;
            log.machineExecutionTime = timeElapsed;
            generateLog(log);
        }
        counter = 0;
        free(dataCopy);

        // Selection Sort Testing
        dataCopy = createArrCopy(testArr, dataSize);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
        printf("\n===== SELECTION SORT START =====\n");
        //counter = bubbleSort(dataCopy, dataSize);         CALL SELECTION SORT HERE
        printf("\n===== SELECTION SORT END =====\n");
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
        if(!isAFK)
        {
            printf("Print sorted array? [y/N]: ");
            scanf(" %c", &cChoice);
            if(cChoice == 'y' || cChoice == 'Y')
            {
                printf("Sorted Array Elements:\n");
                printArrayData(dataCopy, dataSize);
            }
        }
        printf("\nCounter: %d\n", counter);
        seconds = end.tv_sec - begin.tv_sec;
        nanoseconds = end.tv_nsec - begin.tv_nsec;
        timeElapsed = seconds + nanoseconds*1e-9;
        printf("Machine Execution Time: %lf seconds (%lf miliseconds)\n", timeElapsed, timeElapsed * 1000);
        if(doLogging)
        {
            strcpy(log.algoName, "SELECTION SORT");
            log.count = counter;
            log.machineExecutionTime = timeElapsed;
            generateLog(log);
        }
        counter = 0;
        free(dataCopy);

        // Merge Sort Testing
        dataCopy = createArrCopy(testArr, dataSize);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
        printf("\n===== MERGE SORT START =====\n");
        //counter = bubbleSort(dataCopy, dataSize);         CALL MERGE SORT HERE
        printf("\n===== MERGE SORT END =====\n");
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
        if(!isAFK)
        {
            printf("Print sorted array? [y/N]: ");
            scanf(" %c", &cChoice);
            if(cChoice == 'y' || cChoice == 'Y')
            {
                printf("Sorted Array Elements:\n");
                printArrayData(dataCopy, dataSize);
            }
        }
        printf("\nCounter: %d\n", counter);
        seconds = end.tv_sec - begin.tv_sec;
        nanoseconds = end.tv_nsec - begin.tv_nsec;
        timeElapsed = seconds + nanoseconds*1e-9;
        printf("Machine Execution Time: %lf seconds (%lf miliseconds)\n", timeElapsed, timeElapsed * 1000);
        if(doLogging)
        {
            strcpy(log.algoName, "MERGE SORT");
            log.count = counter;
            log.machineExecutionTime = timeElapsed;
            generateLog(log);
        }
        counter = 0;
        free(dataCopy);

        // Algo #5 Testing
        dataCopy = createArrCopy(testArr, dataSize);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
        printf("\n===== ALGO5 SORT START =====\n");
        //counter = bubbleSort(dataCopy, dataSize);         CALL ALGO #5 HERE
        printf("\n===== ALGO5 SORT END =====\n");
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
        if(!isAFK)
        {
            printf("Print sorted array? [y/N]: ");
            scanf(" %c", &cChoice);
            if(cChoice == 'y' || cChoice == 'Y')
            {
                printf("Sorted Array Elements:\n");
                printArrayData(dataCopy, dataSize);
            }
        }
        printf("\nCounter: %d\n", counter);
        seconds = end.tv_sec - begin.tv_sec;
        nanoseconds = end.tv_nsec - begin.tv_nsec;
        timeElapsed = seconds + nanoseconds*1e-9;
        printf("Machine Execution Time: %lf seconds (%lf miliseconds)\n", timeElapsed, timeElapsed * 1000);
        if(doLogging)
        {
            strcpy(log.algoName, "ALGO5");
            log.count = counter;
            log.machineExecutionTime = timeElapsed;
            generateLog(log);
        }
        counter = 0;
        free(dataCopy);

        // Algo #6 Testing
        dataCopy = createArrCopy(testArr, dataSize);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
        printf("\n===== ALGO6 SORT START =====\n");
        //counter = bubbleSort(dataCopy, dataSize);         CALL ALGO #6 HERE
        printf("\n===== ALGO6 SORT END =====\n");
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
        if(!isAFK)
        {
            printf("Print sorted array? [y/N]: ");
            scanf(" %c", &cChoice);
            if(cChoice == 'y' || cChoice == 'Y')
            {
                printf("Sorted Array Elements:\n");
                printArrayData(dataCopy, dataSize);
            }
        }
        printf("\nCounter: %d\n", counter);
        seconds = end.tv_sec - begin.tv_sec;
        nanoseconds = end.tv_nsec - begin.tv_nsec;
        timeElapsed = seconds + nanoseconds*1e-9;
        printf("Machine Execution Time: %lf seconds (%lf miliseconds)\n", timeElapsed, timeElapsed * 1000);
        if(doLogging)
        {
            strcpy(log.algoName, "ALGO6");
            log.count = counter;
            log.machineExecutionTime = timeElapsed;
            generateLog(log);
        }
        counter = 0;
        free(dataCopy);
        */
        if(!isAFK)
            system("PAUSE");
    }
    
    system("PAUSE");

    free(testArr);
    return 0;
}