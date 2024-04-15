#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

void Merge(std::vector<int>& inputVector, std::vector<int>& temp, int leftStart, int rightEnd) {
    int leftEnd = (rightEnd + leftStart) / 2;
    int rightStart = leftEnd + 1;
    int size = rightEnd - leftStart + 1;

    int left = leftStart;
    int right = rightStart;
    int index = leftStart;

    while (left <= leftEnd && right <= rightEnd) {
        if (inputVector[left] <= inputVector[right]) {
            temp[index] = inputVector[left];
            left++;
        } else {
            temp[index] = inputVector[right];
            right++;
        }
        index++;
    }

    std::copy(inputVector.begin() + left, inputVector.begin() + leftEnd + 1, temp.begin() + index);
    std::copy(inputVector.begin() + right, inputVector.begin() + rightEnd + 1, temp.begin() + index);
    std::copy(temp.begin() + leftStart, temp.begin() + leftStart + size, inputVector.begin() + leftStart);
}

void MergeSort(std::vector<int>& inputVector, std::vector<int>& temp, int leftStart, int rightEnd) {
    if (leftStart >= rightEnd) {
        return;
    }

    int middle = (leftStart + rightEnd) / 2;
    MergeSort(inputVector, temp, leftStart, middle);
    MergeSort(inputVector, temp, middle + 1, rightEnd);
    Merge(inputVector, temp, leftStart, rightEnd);
}

void MergeSort(std::vector<int>& inputVector) {
    std::vector<int> temp(inputVector.size());
    MergeSort(inputVector, temp, 0, inputVector.size() - 1);
}

void writeResult(double executionTime, std::string fileName, std::string resultPath) {
    FILE *resultsFile;
    resultsFile = fopen(resultPath.c_str(), "a");
    if (resultsFile == NULL) {
        perror("Erro ao abrir o resultsFile");
        return;
    }

    std::string name = fileName.substr(fileName.find_last_of('/') + 1);
    //fprintf(resultsFile, "C - MergeSort - File: %s\n", name);
    fprintf(resultsFile, "Execution time: %.6f ms\n", executionTime);
    fclose(resultsFile);
}

int main(int argc, char *argv[]) {
    // Default values
    std::string filePath = "../../Dataset/1000k_decreasing.txt";
    std::string resultPath = "../../Results/MergeSort.txt";

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

	auto startTime = std::chrono::high_resolution_clock::now();

	MergeSort(numbers);

	auto endTime = std::chrono::high_resolution_clock::now();

    auto executionTime = std::chrono::duration<double, std::milli>(endTime - startTime);
    std::cout << "Execution time: " << std::fixed << executionTime.count() << " milliseconds" << std::endl;

    writeResult(executionTime.count(), filePath.c_str(), resultPath.c_str());

	return 0;
}