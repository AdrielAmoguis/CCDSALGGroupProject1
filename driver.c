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
#include "quick.c"
//#include "algo6.c"

// Macros
#define INTERVAL 2
#define LOGNAME "OutputData.csv"

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
    unsigned long long count;
} DataLog;

void generateLog(DataLog data)
{
    FILE *fp = fopen(LOGNAME, "a");
    time_t t;
    time(&t);
    fprintf(fp, "%s,%d,%lf,%llu,%s", data.algoName, data.sampleSize, data.machineExecutionTime, data.count, ctime(&t));
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
    int testN[] = {1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152};
    int currN = 0;
    bool isAFK = true, doLogging = false, useScript = false;
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

    printf("Run CCDSALG specs-based test script? [y/N]: ");
    scanf(" %c", &cChoice);

    do
    {
        if(cChoice == 'y' || cChoice == 'Y')
        {
            useScript = true;
            nRuns = 20;
            testArr = malloc(testN[currN] * sizeof(int));
            log.sampleSize = testN[currN];
            dataSize = testN[currN];
            isAFK = true;
            doLogging = true;
        }
        else
        {
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
        }
        
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
            printf("\n===== BUBBLE SORT START =====\n");
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
            counter = bubbleSort(dataCopy, dataSize);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
            printf("\n===== BUBBLE SORT END =====\n");
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
            printf("\nCounter: %llu\n", counter);
            seconds = end.tv_sec - begin.tv_sec;
            nanoseconds = end.tv_nsec - begin.tv_nsec;
            if(begin.tv_nsec > end.tv_nsec) // Clock underflow
            {
                seconds--;
                nanoseconds += 1000000000;
            }
            timeElapsed = (double)seconds + (double)nanoseconds/1000000000.0;
            printf("Machine Execution Time: %lf seconds (%lf miliseconds)\n", timeElapsed, timeElapsed * (double)1000);
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
            printf("\n===== INSERTION SORT START =====\n");
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
            //counter = bubbleSort(dataCopy, dataSize);         CALL INSERTION SORT HERE
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
            printf("\n===== INSERTION SORT END =====\n");
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
            if(begin.tv_nsec > end.tv_nsec) // Clock underflow
            {
                seconds--;
                nanoseconds += 1000000000;
            }
            timeElapsed = (double)seconds + (double)nanoseconds/1000000000.0;
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
            printf("\n===== SELECTION SORT START =====\n");
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
            //counter = bubbleSort(dataCopy, dataSize);         CALL SELECTION SORT HERE
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
            printf("\n===== SELECTION SORT END =====\n");
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
            if(begin.tv_nsec > end.tv_nsec) // Clock underflow
            {
                seconds--;
                nanoseconds += 1000000000;
            }
            timeElapsed = (double)seconds + (double)nanoseconds/1000000000.0;
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
            printf("\n===== MERGE SORT START =====\n");
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
            //counter = bubbleSort(dataCopy, dataSize);         CALL MERGE SORT HERE
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
            printf("\n===== MERGE SORT END =====\n");
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
            if(begin.tv_nsec > end.tv_nsec) // Clock underflow
            {
                seconds--;
                nanoseconds += 1000000000;
            }
            timeElapsed = (double)seconds + (double)nanoseconds/1000000000.0;
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
            */

            // Quick Sort Testing
            dataCopy = createArrCopy(testArr, dataSize);
            printf("\n===== QUICKSORT START =====\n");
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
            counter = quickSort(dataCopy, 0, dataSize-1);    
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
            printf("\n===== QUICKSORT END =====\n");
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
            if(begin.tv_nsec > end.tv_nsec) // Clock underflow
            {
                seconds--;
                nanoseconds += 1000000000;
            }
            timeElapsed = (double)seconds + (double)nanoseconds/1000000000.0;
            printf("Machine Execution Time: %lf seconds (%lf miliseconds)\n", timeElapsed, timeElapsed * 1000);
            counterSums[4] += counter;
            metSums[4] += timeElapsed;
            if(doLogging)
            {
                strcpy(log.algoName, "QUICKSORT");
                log.count = counter;
                log.machineExecutionTime = timeElapsed;
                generateLog(log);
            }
            counter = 0;
            quickCount = 0;
            free(dataCopy);

            /*
            // Algo #6 Testing
            dataCopy = createArrCopy(testArr, dataSize);
            printf("\n===== ALGO6 SORT START =====\n");
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
            //counter = bubbleSort(dataCopy, dataSize);         CALL ALGO #6 HERE
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
            printf("\n===== ALGO6 SORT END =====\n");
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
            if(begin.tv_nsec > end.tv_nsec) // Clock underflow
            {
                seconds--;
                nanoseconds += 1000000000;
            }
            timeElapsed = (double)seconds + (double)nanoseconds/1000000000.0;
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

        FILE *fp = fopen(LOGNAME, "a");
        printf("\nTest Summary:\n\n");
        time_t currTime; time(&currTime);
        fprintf(fp, "\n\nTest Summary:\n", ctime(&currTime));

        // Bubble Sort
        timeAve = metSums[0] / nRuns;
        countAve = counterSums[0] / nRuns;
        printf("Bubble Sort Average MET = %lf\n", timeAve);
        printf("Bubble Sort Average TFC = %llu\n\n", countAve);
        fprintf(fp, "Bubble Sort Average MET,%lf\n", timeAve);
        fprintf(fp, "Bubble Sort Average TFC,%llu\n\n", countAve);

        // Insertion Sort
        timeAve = metSums[1] / nRuns;
        countAve = counterSums[1] / nRuns;
        printf("Insertion Sort Average MET = %lf\n", timeAve);
        printf("Insertion Sort Average TFC = %llu\n\n", countAve);
        fprintf(fp, "Insertion Sort Average MET,%lf\n", timeAve);
        fprintf(fp, "Insertion Sort Average TFC,%llu\n\n", countAve);

        // Selection Sort
        timeAve = metSums[2] / nRuns;
        countAve = counterSums[2] / nRuns;
        printf("Selection Sort Average MET = %lf\n", timeAve);
        printf("Selection Sort Average TFC = %llu\n\n", countAve);
        fprintf(fp, "Selection Sort Average MET,%lf\n", timeAve);
        fprintf(fp, "Selection Sort Average TFC,%llu\n\n", countAve);

        // Merge Sort
        timeAve = metSums[3] / nRuns;
        countAve = counterSums[3] / nRuns;
        printf("Merge Sort Average MET = %lf\n", timeAve);
        printf("Merge Sort Average TFC = %llu\n\n", countAve);
        fprintf(fp, "Merge Sort Average MET,%lf\n", timeAve);
        fprintf(fp, "Merge Sort Average TFC,%llu\n\n", countAve);

        // Algo5
        timeAve = metSums[4] / nRuns;
        countAve = counterSums[4] / nRuns;
        printf("Algo5 Sort Average MET = %lf\n", timeAve);
        printf("Algo5 Sort Average TFC = %llu\n\n", countAve);
        fprintf(fp, "QuickSort Average MET,%lf\n", timeAve);
        fprintf(fp, "QuickSort Average TFC,%llu\n\n", countAve);

        // Algo6
        timeAve = metSums[5] / nRuns;
        countAve = counterSums[5] / nRuns;
        printf("Algo6 Sort Average MET = %lf\n", timeAve);
        printf("Algo6 Sort Average TFC = %llu\n\n", countAve);
        fprintf(fp, "Algo6 Sort Average MET,%lf\n", timeAve);
        fprintf(fp, "Algo6 Sort Average TFC,%llu\n\n", countAve);

        fprintf(fp, "\nITERATION END\n\n\n");

        fclose(fp);
        free(testArr);
        currN++;
    } while(useScript && currN < 12);
    

    system("PAUSE");

    return 0;
}