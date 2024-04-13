# Benchmark Languages

Faça um relatório contendo gráficos que mostram comparativos de desempenhos de cada
algoritmo/implementação para cada tipo de entrada. Crie gráficos que descrevem os perfis
(média, mediana, quartil superior e inferior, etc) dos dados utilizados também. Descreva os
detalhes dos experimentos realizados (geração dos arquivos de entrada, ambiente computacional utilizado nos experimentos, etc) e discuta sobre os resultados observados.

Linguagens C, C++ e Java
Sorts: InsertionSort, BucketSort e MergeSort
Casos: 
a) Números inteiros/reais aleatórios
b) Números inteiros/reais em ordem não-ascendente
c) Números inteiros/reais quase ordenados (>= 95% de valores em ordem)

Hardware do computador em que rodou os testes:
Processador: Ryzen 5700X
Memória: 4x8Gb 3600Mhz
Placa Mãe: MSI MAG B550 Tomahawk
Armazenamento: SSD NVMe PCIe4.0 NV7000

Versão GCC para C: 6.3.0 (MinGW.org GGC-6.3.0-1)
Versão do Python: 3.12.3
Versão do Java: “22” 2024-03-19

Rodar pelo menos 3 vezes cada algoritmo com cada entrada
comando pra loopar o executável
for /L %i in (1,1,10) do nomeexecutavel "entrada.txt" "saida.txt" 10000

Para os algoritmos em C e Java, iremos testar compilando o código com as flags de otimização -O0, e -Ofast para ver a diferença de desempenho.

# Produzir relatório com os resultados obtidos
- Criar a pasta "Results" na raiz do projeto
- Rodar o script "run.sh" para compilar e rodar os testes