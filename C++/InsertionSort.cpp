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

int main() {
    // Ler dados do arquivo
    std::ifstream datasetFile("../../Dataset/100k_parc_ordenado.txt");
    if (!datasetFile) {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }
    int number;
    std::vector<int> vector;
    while (datasetFile >> number) {
        vector.push_back(number);
    }
    datasetFile.close();

    auto startTime = std::chrono::high_resolution_clock::now();
    InsertionSort(vector, 100000);
    auto endTime = std::chrono::high_resolution_clock::now();

    auto executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "Execution time: " << executionTime.count() << " microseconds" << std::endl;

    return 0;
}