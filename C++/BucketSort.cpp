#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

// Function to sort a vector using the Quick Sort algorithm
void quickSort(std::vector<int>& inputVector, int start, int end) {
    if (start < end) {
        int pivot = inputVector[end];
        int smallerElementIndex = start - 1;

        for (int currentIndex = start; currentIndex < end; currentIndex++) {
            if (inputVector[currentIndex] <= pivot) {
                smallerElementIndex++;
                std::swap(inputVector[smallerElementIndex], inputVector[currentIndex]);
            }
        }
        std::swap(inputVector[smallerElementIndex + 1], inputVector[end]);

        int pivotIndex = smallerElementIndex + 1;
        quickSort(inputVector, start, pivotIndex - 1);
        quickSort(inputVector, pivotIndex + 1, end);
    }
}

// Bucket Sort function
std::vector<int> BucketSort(const std::vector<int>& inputVector) {

    int maxValue = *std::max_element(inputVector.begin(), inputVector.end());
    int minValue = *std::min_element(inputVector.begin(), inputVector.end());

    // Determine the number of buckets
    int bucketCount = (maxValue - minValue) / 10 + 1;

    // Create buckets
    std::vector<std::vector<int>> buckets(bucketCount);

    // Distribute elements into buckets
    for (int i = 0; i < inputVector.size(); i++) {
        int bucketIndex = (inputVector[i] - minValue) / 10;
        buckets[bucketIndex].push_back(inputVector[i]);
    }

    // Sort elements in each bucket using Quick Sort
    for (int i = 0; i < buckets.size(); i++) {
        quickSort(buckets[i], 0, buckets[i].size() - 1);
    }

    // Concatenate sorted buckets into a single vector
    std::vector<int> sortedVector;
    for (int i = 0; i < buckets.size(); i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            sortedVector.push_back(buckets[i][j]);
        }
    }

    return sortedVector;
}

void writeResult(double executionTime, std::string fileName, std::string resultPath) {
    FILE *resultsFile;
    resultsFile = fopen(resultPath.c_str(), "a");
    if (resultsFile == NULL) {
        perror("Erro ao abrir o resultsFile");
        return;
    }

    std::string name = fileName.substr(fileName.find_last_of('/') + 1);
    //fprintf(resultsFile, "C - BucketSort - File: %s\n", name);
    fprintf(resultsFile, "Execution time: %.6f ms\n", executionTime);
    fclose(resultsFile);
}

int main(int argc, char *argv[]) {
    // Default values
    std::string filePath = "../../Dataset/1000k_parc_ordenado.txt";
    std::string resultPath = "../../Results/BucketSort.txt";

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

    std::ifstream datasetFile(filePath.c_str());

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

    // Ordenar numbers usando Bucket Sort
    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<int> result = BucketSort(numbers);

    auto endTime = std::chrono::high_resolution_clock::now();

    auto executionTime = std::chrono::duration<double, std::milli>(endTime - startTime);
    std::cout << "Execution time: " << std::fixed << executionTime.count() << " milliseconds" << std::endl;

    // std::cout << "numbers Ordenado:" << std::endl;
    // for (int i = 0; i < result.size(); i++) {
    //     std::cout << result[i] << " ";
    // }
    // std::cout << std::endl;

    writeResult(executionTime.count(), filePath, resultPath);

    return 0;
}