#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

std::vector<int> Merge(std::vector<int> left, std::vector<int> right) {
    int leftSize = left.size();
    int rightSize = right.size();

    std::vector<int> merged; // Initializes an empty vector to store the merged result

    int leftIndex = 0, rightIndex = 0; // leftIndex for left vector, rightIndex for right vector

    // Merge elements from left and right vectors in sorted order
    while (leftIndex < leftSize && rightIndex < rightSize) {
        if (left[leftIndex] <= right[rightIndex]) {
            merged.push_back(left[leftIndex]);
            leftIndex++;
        } else {
            merged.push_back(right[rightIndex]);
            rightIndex++;
        }
    }

    // If there are remaining elements in right vector, add them to the result
    while (rightIndex < rightSize) {
        merged.push_back(right[rightIndex]);
        rightIndex++;
    }

    // If there are remaining elements in left vector, add them to the result
    while (leftIndex < leftSize) {
        merged.push_back(left[leftIndex]);
        leftIndex++;
    }

    return merged;
}

std::vector<int> MergeSort(std::vector<int>& inputVector) {

    int vectorSize = inputVector.size();

    if (vectorSize <= 1) {
        return inputVector;
    }

    std::vector<int> leftHalf(inputVector.begin(), inputVector.begin() + vectorSize / 2);
    std::vector<int> rightHalf(inputVector.begin() + vectorSize / 2, inputVector.end());

    return Merge(MergeSort(leftHalf), MergeSort(rightHalf));
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
    std::string filePath = "../../Dataset/1000k_parc_ordenado.txt";
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

	std::vector<int> ordered;

	auto startTime = std::chrono::high_resolution_clock::now();

	ordered = MergeSort(numbers);

	auto endTime = std::chrono::high_resolution_clock::now();

    auto executionTime = std::chrono::duration<double, std::milli>(endTime - startTime);
    std::cout << "Execution time: " << std::fixed << executionTime.count() << " milliseconds" << std::endl;
    
	// int tam = ordered.size();
	// for (int i = 0; i < tam; i++) {
	// 	std::cout << ordered[i] << std::endl;
	// }

    writeResult(executionTime.count(), filePath.c_str(), resultPath.c_str());

	return 0;
}