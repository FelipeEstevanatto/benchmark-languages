#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

std::vector<int> InsertionSort(std::vector<int>& numbers, int arraySize){
    int currentIndex, previousIndex;

    for(currentIndex = 1; currentIndex < arraySize; currentIndex++){
        previousIndex = currentIndex - 1;
        while(previousIndex >= 0 && numbers[previousIndex+1] < numbers[previousIndex]){
            int temp = numbers[previousIndex];
            numbers[previousIndex] = numbers[previousIndex+1];
            numbers[previousIndex+1] = temp;
            previousIndex--;
        }
    }

    return numbers;
}

void writeResult(clock_t executionTime, char* fileName, char* resultPath) {
    FILE *resultsFile;
    resultsFile = fopen(resultPath, "a");
    if (resultsFile == NULL) {
        perror("Erro ao abrir o resultsFile");
        return;
    }

    char *name = strrchr(fileName, '/');
    fprintf(resultsFile, "C - InsertionSort - File: %s\n", name);
    fprintf(resultsFile, "Execution time: %lf ms\n", ((double)executionTime) / ((CLOCKS_PER_SEC / 1000)));
    fclose(resultsFile);
}

int main(int argc, char *argv[]) {
    // Default values
    std::string filePath = "../../Dataset/1000k_parc_ordenado.txt";
    std::string resultPath = "../../Results/InsertionSort.txt";

    size_t maxSize = 1000000;

    // Check if the user provided the input file
    if (argc >= 2) {
        filePath = argv[1];
    }

    if (argc >= 3) {
        resultPath = argv[2];
    }

    if (argc >= 4) {
        maxSize = std::stoi(argv[3]);
    }

    std::ifstream datasetFile(filePath);

    if (!datasetFile) {
        std::cerr << "Failed to open dataset file" << std::endl;
        return 1;
    }
    
    int number;
    std::vector<int> numbers;
    while (datasetFile >> number) {
        numbers.push_back(number);
        if (numbers.size() == maxSize) {
            break;
        }
    }
    datasetFile.close();

    auto startTime = std::chrono::high_resolution_clock::now();
    numbers = InsertionSort(numbers, maxSize);
    auto endTime = std::chrono::high_resolution_clock::now();

    auto executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "Execution time: " << executionTime.count() << " microseconds" << std::endl;

    // for (int i = 0; i < numbers.size(); i++) {
    //     std::cout << numbers[i] << " ";
    // }

    writeResult(executionTime, filePath, resultPath);

    return 0;
}