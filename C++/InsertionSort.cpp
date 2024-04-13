#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

void InsertioSort(std::vector<int> vet, int tam){

  auto inicio = std::chrono::high_resolution_clock::now();

  int i,j;

  for(i = 1; i<tam; i++){
    j = i - 1;
    while(j>=0 && vet[j+1] < vet[j]){
      int aux = vet[j];
      vet[j] = vet[j+1];
      vet[j+1] = aux;
      j--;
      //std::cout<<"trocou";
    }
  }

    auto fim = std::chrono::high_resolution_clock::now();

    auto duracao = std::chrono::duration_cast<std::chrono::seconds>(fim - inicio);


    std::cout << "Tempo de execução: " << duracao.count() << " microssegundos" << std::endl;


  for (i = 0; i < tam; i++) {
      std::cout << vet[i] << " ";
  }
  std::cout << std::endl;


}

int main() {

  std::vector<int> vet;

  std::ifstream arquivo("../Dataset/dataset_95_sorted.txt");
  std::string palavra;

  if(arquivo.is_open()){
    while(arquivo >> palavra){

        //std::cout<<palavra <<std::endl;
        int numero =  std::stoi(palavra);
        vet.push_back(numero);
    }
    arquivo.close();
  }else{
    std::cout<<"arquivo não foi aberto"<<std::endl;
  }

  InsertioSort(vet, 1000000);

  return 0;

}