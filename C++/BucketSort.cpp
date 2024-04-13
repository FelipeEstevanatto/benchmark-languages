#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

// Função para ordenar um vetor usando o algoritmo Quick Sort
void quickSort(std::vector<int>& vetor, int inicio, int fim) {
    if (inicio < fim) {
        int pivo = vetor[fim];
        int i = inicio - 1;

        for (int j = inicio; j < fim; j++) {
            if (vetor[j] <= pivo) {
                i++;
                std::swap(vetor[i], vetor[j]);
            }
        }
        std::swap(vetor[i + 1], vetor[fim]);

        int indice_pivo = i + 1;
        quickSort(vetor, inicio, indice_pivo - 1);
        quickSort(vetor, indice_pivo + 1, fim);
    }
}

// Função de Bucket Sort
std::vector<int> BucketSort(const std::vector<int>& vet) {


    int maior = *std::max_element(vet.begin(), vet.end());
    int menor = *std::min_element(vet.begin(), vet.end());

    // Determinar o número de baldes
    int numBaldes = (maior - menor) / 10 + 1;

    // Criar baldes
    std::vector<std::vector<int>> baldes(numBaldes);

    // Distribuir elementos nos baldes
    for (int i = 0; i < vet.size(); i++) {
        int indice = (vet[i] - menor) / 10;
        baldes[indice].push_back(vet[i]);
    }

    // Ordenar elementos em cada balde usando o Quick Sort
    for (int i = 0; i < baldes.size(); i++) {
        quickSort(baldes[i], 0, baldes[i].size() - 1);
    }

    // Concatenar baldes ordenados em um único vetor
    std::vector<int> resultado;
    for (int i = 0; i < baldes.size(); i++) {
        for (int j = 0; j < baldes[i].size(); j++) {
            resultado.push_back(baldes[i][j]);
        }
    }

    return resultado;
}

int main() {
    // Ler dados do arquivo
    std::ifstream arquivo("../Dataset/decreasing_1M.txt");
    int numero;
    std::vector<int> vetor;
    while (arquivo >> numero) {
        vetor.push_back(numero);
    }
    arquivo.close();

    // Ordenar vetor usando Bucket Sort

    auto inicio = std::chrono::high_resolution_clock::now();

    std::vector<int> resultado = BucketSort(vetor);

    auto fim = std::chrono::high_resolution_clock::now();

    // Exibir vetor ordenado
    std::cout << "Vetor Ordenado:" << std::endl;
    for (int i = 0; i < resultado.size(); i++) {
        std::cout << resultado[i] << " ";
    }
    std::cout << std::endl;

    auto duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - inicio);
    std::cout << "Tempo de execução: " << duracao.count() << " microsegundos" << std::endl;

    return 0;
}