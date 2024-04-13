#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>


std::vector <int> Mescla(std::vector <int> esq, std::vector <int> dir){

    int tamEsq = esq.size();
    int tamDir = dir.size();

    std::vector <int> ordenado;//inicia um vetor com o tamanho dos dois subvetores somados

    int ie = 0, jd = 0;// i(esq), j(dir), k(ordenado)

    while( ie < tamEsq && jd < tamDir){
        if(esq[ie] <= dir[jd]){
            ordenado.push_back(esq[ie]);
            ie++;
        }
        else{
            ordenado.push_back(dir[jd]);
            jd++;   
        }
    }


    while (jd < tamDir)
    {
        ordenado.push_back(dir[jd]);
        jd++;
    }


    while (ie < tamEsq)
    {
        ordenado.push_back(esq[ie]);
        ie++;   
    }



    return ordenado;

}

std::vector <int> MergeSort(std::vector <int> vet){

    int tam = vet.size();

    if(tam<=1){
       // std::cout<<"Vetor ordenado";
        return vet;
    }
    std::vector<int> esq(vet.begin(), vet.begin() + tam / 2);
    std::vector<int> dir(vet.begin() + tam / 2, vet.end());


   return Mescla(MergeSort(esq), MergeSort(dir));

}


int main() {

  std::vector<int> vet;

  std::ifstream arquivo("../Dataset/dataset_non_ascending.txt");
  std::string palavra;

///////////////////ABRINDO O ARQUIVO ////////////////////////////////////////////////

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
////////////////////////////////////////////////////////////////////////////////////////////

    std:: vector <int> ordenado;

    auto inicio = std::chrono::high_resolution_clock::now(); // calculando tempo de execução

        ordenado = MergeSort(vet);


    auto fim = std::chrono::high_resolution_clock::now();

    auto duracao = std::chrono::duration_cast<std::chrono::seconds>(fim - inicio);

    int tam = ordenado.size();

    for (int i = 0; i < tam; i++) {
        std::cout << ordenado[i] << " ";
    }




    std::cout << "Tempo de execução: " << duracao.count() << "segundos" << std::endl;  // resultado do tempo de execução

 return 0;

}