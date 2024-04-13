#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

void InsertionSort(std::vector<int>& numbers, int arraySize){
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

    // for (currentIndex = 0; currentIndex < arraySize; currentIndex++) {
    //     std::cout << numbers[currentIndex] << " ";
    // }
    // std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    // Default values
    std::string filePath = "../../Dataset/100k_parc_ordenado.txt";
    size_t maxSize = 100000;

    // Check if the user provided the input file
    if (argc >= 2) {
        filePath = argv[1];
    }

    if (argc >= 3) {
        maxSize = std::stoi(argv[2]);
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
    InsertionSort(numbers, 100000);
    auto endTime = std::chrono::high_resolution_clock::now();

    auto executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "Execution time: " << executionTime.count() << " microseconds" << std::endl;

    return 0;
}