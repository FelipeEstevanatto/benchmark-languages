#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Average complexity: O(nlog(n))
// Worst complexity: O(nlog(n))

void merge(int* array, int left, int middle, int right) {
    int leftSize = middle - left + 1;
    int rightSize = right - middle;

    int* leftArray = malloc(leftSize * sizeof(int));
    int* rightArray = malloc(rightSize * sizeof(int));

    memcpy(leftArray, &array[left], leftSize * sizeof(int));
    memcpy(rightArray, &array[middle + 1], rightSize * sizeof(int));

    int leftIndex = 0;
    int rightIndex = 0;
    int mergedIndex = left;

    while (leftIndex < leftSize && rightIndex < rightSize) {
        if (leftArray[leftIndex] <= rightArray[rightIndex]) {
            array[mergedIndex] = leftArray[leftIndex];
            leftIndex++;
        } else {
            array[mergedIndex] = rightArray[rightIndex];
            rightIndex++;
        }
        mergedIndex++;
    }

    while (leftIndex < leftSize) {
        array[mergedIndex] = leftArray[leftIndex];
        leftIndex++;
        mergedIndex++;
    }

    while (rightIndex < rightSize) {
        array[mergedIndex] = rightArray[rightIndex];
        rightIndex++;
        mergedIndex++;
    }

    free(leftArray);
    free(rightArray);
}

void mergeSort(int* array, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(array, left, middle);
        mergeSort(array, middle + 1, right);

        merge(array, left, middle, right);
    }
}

void writeResult(clock_t executionTime, char* fileName, char* resultPath) {
    FILE *resultsFile;
    resultsFile = fopen(resultPath, "a");
    if (resultsFile == NULL) {
        perror("Erro ao abrir o resultsFile");
        return;
    }

    char *name = strrchr(fileName, '/');
    //fprintf(resultsFile, "C - MergeSort - File: %s\n", name);
    fprintf(resultsFile, "Execution time: %lf ms\n", ((double)executionTime) / ((CLOCKS_PER_SEC / 1000)));
    fclose(resultsFile);
}

int main(int argc, char *argv[]) {
    // Default values
    char filePath[256] = "../../Dataset/1000k_parc_ordenado.txt";
    char resultPath[256] = "../../Results/MergeSort.txt";
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
    mergeSort(numbers, 0, maxSize - 1);
    executionTime = clock() - executionTime;
    printf("Execution time: %lf ms\n", ((double)executionTime) / ((CLOCKS_PER_SEC / 1000)));

    writeResult(executionTime, filePath, resultPath);

    free(numbers);
    return 0;
}