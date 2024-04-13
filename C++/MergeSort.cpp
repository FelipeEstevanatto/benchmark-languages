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

	std::vector <int> ordered;

	auto startTime = std::chrono::high_resolution_clock::now();

	ordered = MergeSort(vector);

	auto endTime = std::chrono::high_resolution_clock::now();

	auto executionTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

	// int tam = ordered.size();
	// for (int i = 0; i < tam; i++) {
	// 	std::cout << ordered[i] << " ";
	// }

    std::cout << "Execution time: " << executionTime.count() << " microseconds" << std::endl;

	return 0;
}