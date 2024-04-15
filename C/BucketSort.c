#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Average complexity: O(n+k)
// Worst case complexity: O(n^2)

void bucketSort(int* inputArray, int arraySize) {
    int index, innerIndex;
    int minValue = inputArray[0], maxValue = inputArray[0];

    // Find the minimum and maximum values in the array
    for (index = 1; index < arraySize; index++) {
        if (inputArray[index] < minValue) {
            minValue = inputArray[index];
        } else if (inputArray[index] > maxValue) {
            maxValue = inputArray[index];
        }
    }

    // Create buckets for each possible value in the range minValue to maxValue
    int range = maxValue - minValue + 1;
    int* bucketArray = malloc(range * sizeof(int));
    if (bucketArray == NULL) {
        perror("Error allocating memory");
        return;
    }

    for (index = 0; index < range; index++) {
        bucketArray[index] = 0;
    }

    // Count the occurrences of each number
    for (index = 0; index < arraySize; index++) {
        (bucketArray[inputArray[index] - minValue])++;
    }

    // Reconstruct the array with the sorted numbers
    for (index = 0, innerIndex = 0; index < range; index++) {
        for (; bucketArray[index] > 0; (bucketArray[index])--) {
            inputArray[innerIndex++] = index + minValue;
        }
    }

    free(bucketArray);
}

void writeResult(clock_t executionTime, char* fileName, char* resultPath) {
    FILE *resultsFile;
    resultsFile = fopen(resultPath, "a");
    if (resultsFile == NULL) {
        perror("Erro ao abrir o resultsFile");
        return;
    }

    char *name = strrchr(fileName, '/');
    //fprintf(resultsFile, "C - BucketSort - File: %s\n", name);
    fprintf(resultsFile, "Execution time: %lf ms\n", ((double)executionTime) / ((CLOCKS_PER_SEC / 1000)));
    fclose(resultsFile);
}

int main(int argc, char *argv[]) {
    // Default values
    char filePath[256] = "../../Dataset/1000k_decreasing.txt";
    char resultPath[256] = "../../Results/BucketSort.txt";
    size_t maxSize = 1000000;

    // Check if the user provided the input file
    if (argc >= 2) {
        strncpy(filePath, argv[1], sizeof(filePath) - 1);
        filePath[sizeof(filePath) - 1] = '\0'; // Ensure null-termination
    }

    if (argc >= 3) {
        strncpy(resultPath, argv[2], sizeof(resultPath) - 1);
        resultPath[sizeof(resultPath) - 1] = '\0'; // Ensure null-termination
    }

    if (argc >= 4) {
        maxSize = (size_t)atoi(argv[3]);
    }

    FILE *datasetFile = fopen(filePath, "r");

    if (!datasetFile) {
        fprintf(stderr, "Failed to open dataset file\n");
        return 1;
    }

    int number;
    clock_t executionTime;
    int *numbers = malloc(maxSize * sizeof(int));
    size_t count = 0;
    while (fscanf(datasetFile, "%d", &number) == 1 && count < maxSize) {
        numbers[count++] = number;
    }
    fclose(datasetFile);

    executionTime = clock();
    bucketSort(numbers, maxSize);
    executionTime = clock() - executionTime;
    printf("Execution time: %lf ms\n", ((double)executionTime) / ((CLOCKS_PER_SEC / 1000)));

    free(numbers);

    writeResult(executionTime, filePath, resultPath);

    return 0;
}