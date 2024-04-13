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

int main() {
    // Ler dados do arquivo
    std::ifstream datasetFile("../../Dataset/100k_parc_ordenado.txt");
    if (!datasetFile) {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }
    int number;
    std::vector<int> vetor;
    while (datasetFile >> number) {
        vetor.push_back(number);
    }
    datasetFile.close();

    // Ordenar vetor usando Bucket Sort
    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<int> result = BucketSort(vetor);

    auto endTime = std::chrono::high_resolution_clock::now();

    // Exibir vetor ordenado
    // std::cout << "Vetor Ordenado:" << std::endl;
    // for (int i = 0; i < result.size(); i++) {
    //     std::cout << result[i] << " ";
    // }
    // std::cout << std::endl;

    auto executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "Execution time: " << executionTime.count() << " microseconds" << std::endl;

    return 0;
}