#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Average complexity: O(n^2)
// Worst case complexity: O(n^2)

void insertionSort(int* array, int arraySize) {
    int currentIndex, currentValue;
    for (int sortedIndex = 1; sortedIndex < arraySize; sortedIndex++) {
        currentIndex = sortedIndex - 1;
        currentValue = array[sortedIndex];
    
        while (currentIndex >= 0 && currentValue < array[currentIndex]) {
            array[currentIndex + 1] = array[currentIndex];
            currentIndex--;
        }
        array[currentIndex + 1] = currentValue;
    }
}

int main(int argc, char *argv[]) {
    // Default values
    char filePath[256] = "../../Dataset/100k_parc_ordenado.txt";
    size_t maxSize = 100000;

    // Check if the user provided the input file
    if (argc >= 2) {
        strncpy(filePath, argv[1], sizeof(filePath) - 1);
        filePath[sizeof(filePath) - 1] = '\0'; // Ensure null-termination
    }

    if (argc >= 3) {
        maxSize = (size_t)atoi(argv[2]);
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
    insertionSort(numbers, maxSize);
    executionTime = clock() - executionTime;
    printf("Execution time: %lf ms\n", ((double)executionTime) / ((CLOCKS_PER_SEC / 1000)));
    
    free(numbers);
    return 0;
}