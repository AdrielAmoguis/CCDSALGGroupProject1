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

// This will be removed after all algos are implemented
#if _WIN32 || _WIN64
    #include <windows.h>
#else
    #include <unistd.h>
#endif

// Algorithms
#include "GenerateData.c"
#include "bubble.c"
//#include "insertion.c"
//#include "selection.c"
//#include "merge.c"
//#include "algo5.c"
//#include "algo6.c"

// Macros
#define INTERVAL 5

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

    unsigned long long counterSums[6] = {0,0,0,0,0,0};
    double metSums[6] = {0,0,0,0,0,0};

    printf("Run for how many times? : ");
    scanf("%d", &nRuns);

    printf("Enter n: ");
    scanf("%d", &dataSize);
    testArr = malloc(dataSize * sizeof(int));
    log.sampleSize = dataSize;

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
        printf("\nProgram Iteration M = %d of %d\n\n", programRun+1, nRuns);

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
        counterSums[0] += counter;
        metSums[0] += timeElapsed;
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
        counterSums[1] += counter;
        metSums[1] += timeElapsed;
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
        counterSums[2] += counter;
        metSums[2] += timeElapsed;
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
        counterSums[3] += counter;
        metSums[3] += timeElapsed;
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
        counterSums[4] += counter;
        metSums[4] += timeElapsed;
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
        printf("Machine Execution Time: %lf seconds (%lf miliseconds)\n", timeElapsed, timeElapsed * 1000);.
        counterSums[5] += counter;
        metSums[5] += timeElapsed;
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

        // This will delay code execution by 5 seconds to reset the randomizer seed
        // This will be removed after all algos are implemented
        #if _WIN32 || _WIN64
            Sleep(INTERVAL*1000);
        #else 
            sleep(INTERVAL);
        #endif
    }
    
    // Compute for the MET and TFC averages per algorithm
    double timeAve;
    unsigned long long countAve;

    FILE *fp = fopen("testLog.txt", "a");
    printf("\nTest Summary:\n\n");
    fprintf(fp, "\n\nTest Summary:\n");

    // Bubble Sort
    timeAve = metSums[0] / nRuns;
    countAve = counterSums[0] / nRuns;
    printf("Bubble Sort Average MET = %lf\n", timeAve);
    printf("Bubble Sort Average TFC = %ld\n\n", countAve);
    fprintf(fp, "Bubble Sort Average MET = %lf\n", timeAve);
    fprintf(fp, "Bubble Sort Average TFC = %ld\n\n", countAve);

    // Insertion Sort
    timeAve = metSums[1] / nRuns;
    countAve = counterSums[1] / nRuns;
    printf("Insertion Sort Average MET = %lf\n", timeAve);
    printf("Insertion Sort Average TFC = %ld\n\n", countAve);
    fprintf(fp, "Insertion Sort Average MET = %lf\n", timeAve);
    fprintf(fp, "Insertion Sort Average TFC = %ld\n\n", countAve);

    // Selection Sort
    timeAve = metSums[2] / nRuns;
    countAve = counterSums[2] / nRuns;
    printf("Selection Sort Average MET = %lf\n", timeAve);
    printf("Selection Sort Average TFC = %ld\n\n", countAve);
    fprintf(fp, "Selection Sort Average MET = %lf\n", timeAve);
    fprintf(fp, "Selection Sort Average TFC = %ld\n\n", countAve);

    // Merge Sort
    timeAve = metSums[3] / nRuns;
    countAve = counterSums[3] / nRuns;
    printf("Merge Sort Average MET = %lf\n", timeAve);
    printf("Merge Sort Average TFC = %ld\n\n", countAve);
    fprintf(fp, "Merge Sort Average MET = %lf\n", timeAve);
    fprintf(fp, "Merge Sort Average TFC = %ld\n\n", countAve);

    // Algo5
    timeAve = metSums[4] / nRuns;
    countAve = counterSums[4] / nRuns;
    printf("Algo5 Sort Average MET = %lf\n", timeAve);
    printf("Algo5 Sort Average TFC = %ld\n\n", countAve);
    fprintf(fp, "Algo5 Sort Average MET = %lf\n", timeAve);
    fprintf(fp, "Algo5 Sort Average TFC = %ld\n\n", countAve);

    // Algo6
    timeAve = metSums[5] / nRuns;
    countAve = counterSums[5] / nRuns;
    printf("Algo6 Sort Average MET = %lf\n", timeAve);
    printf("Algo6 Sort Average TFC = %ld\n\n", countAve);
    fprintf(fp, "Algo6 Sort Average MET = %lf\n", timeAve);
    fprintf(fp, "Algo6 Sort Average TFC = %ld\n\n", countAve);

    fclose(fp);

    system("PAUSE");

    free(testArr);
    return 0;
}