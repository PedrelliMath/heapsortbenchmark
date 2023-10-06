/*  
    PROCESSO AVALIATIVO N2 – ESTRUTURA DE DADOS
    EQUIPE
    NOMES: Matheus Eduardo Pedrelli Maurico

    CONSEGUIU CHEGAR NO RESULTADO?
    R: Sim
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>
#include <chrono>
#include <iomanip>
#include <unordered_map>
#include <string>

std::vector<int> generateRandomVector(int arraySize){
    std::vector<int> array(arraySize);
    for (int i = 0; i < arraySize; ++i) {
        array[i] = i + 1;
    }
    std::random_shuffle(array.begin(), array.end());
    return array;
}

std::vector<int> generateIncreasingVector(int arraySize){
    std::vector<int> array(arraySize);
    for(int i = 0; i < arraySize; i++){
        array[i] = i + 1;
    }
    return array;
}

std::vector<int> generateDecreasingVector(int arraySize){
    std::vector<int> array(arraySize);
    for(int i = arraySize - 1; i >= 0; i--){
        array[i] = arraySize - i;
    }
    return array;
}

std::vector<int> createVector(int type, int arraySize){
    std::vector<int> array;
    switch(type){
        case 1: array = generateRandomVector(arraySize); break;
        case 2: array = generateDecreasingVector(arraySize); break;
        case 3: array = generateIncreasingVector(arraySize); break;
        default: break;
    }
    return array;
}

void printVector(std::vector<int>& arr){
    unsigned int size = arr.size();
    for(int i = 0; i < size; i++){
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

void printTableHead(std::vector<std::string>& tableHead) {
    unsigned int tableHeadSize = tableHead.size();
    
    for (unsigned int i = 0; i < tableHeadSize; i++) {
        std::cout << "+---------------------";
    }
    std::cout << "+" << std::endl;

    for (unsigned int i = 0; i < tableHeadSize; i++) {
        std::cout << "| " << std::setw(18) << tableHead[i] << " ";
    }
    std::cout << "|" << std::endl;

    for (unsigned int i = 0; i < tableHeadSize; i++) {
        std::cout << "+---------------------";
    }
    std::cout << "+" << std::endl;
}

void printTableBody(const std::vector<std::vector<double>>& tableBody) {
    unsigned int numRows = tableBody[0].size();

    for (unsigned int row = 0; row < numRows; row++) {
        for (unsigned int col = 0; col < tableBody.size(); col++) {
            std::cout << "| " << std::setw(18) << tableBody[col][row] << " ";
        }
        std::cout << "|" << std::endl;

        if (row == numRows - 1) {
            for (unsigned int col = 0; col < tableBody.size(); col++) {
                std::cout << "+---------------------";
            }
            std::cout << "+" << std::endl;
        }
    }
}

 std::unordered_map<std::string, int> createHashTable(){
    std::unordered_map<std::string, int> hashTable;
    hashTable["-a"] = 1;
    hashTable["-b"] = 2;
    hashTable["-w"] = 3;
    return hashTable;
}

void generateTable(std::vector<std::string>& tableHead, std::vector<std::vector<double>>& tableBody){   
    printTableHead(tableHead);
    printTableBody(tableBody);
}

struct Counters{
    int comparisons = 0;
    int operations = 0;
};

// Função auxiliar para transformar um sub-árvore em um Heap Max
void heapify(std::vector<int>& arr, int n, int root, struct Counters& counters) {
    int largest = root; // Inicializa o maior como a raiz
    int left_child = 2 * root + 1; // Calcula o índice do filho da esquerda
    int right_child = 2 * root + 2; // Calcula o índice do filho da direita
    counters.comparisons++;
    // Se o filho da esquerda é maior que o maior até agora
    if (left_child < n && arr[left_child] > arr[largest])
        largest = left_child;
    counters.comparisons++;
    // Se o filho da direita é maior que o maior até agora
    if (right_child < n && arr[right_child] > arr[largest])
        largest = right_child;
    // Se o maior não é a raiz
    counters.comparisons++;
    if (largest != root) {
        counters.operations++;
        std::swap(arr[root], arr[largest]);
        // Recursivamente transforma a sub-árvore
        heapify(arr, n, largest, counters);
    }
}

// Função principal que implementa o Heap Sort
void heap_sort(std::vector<int>& arr, struct Counters& counters) {
    int n = arr.size();
    // Transforma a lista numa Max Heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, counters);
    // Extrai elementos da Heap Max
    for (int i = n - 1; i >= 0; i--) {
        counters.operations++;
        std::swap(arr[0], arr[i]); // Trocamos a raiz pelo último elemento do último nível
        heapify(arr, i, 0, counters); // Revalida a lista para Max Heap
    }
}

int main(int argc, char* argv[]){
    if(argc < 3){
        std::cout << "Argumentos faltandos...\n";
        return 1;
    }
    
    unsigned int arraySizeArgument = 0, timesSamples = 0;
    std::string caseArgument;

    try {
        caseArgument = argv[1];
        arraySizeArgument = std::stoi(argv[2]);
        timesSamples = std::stoi(argv[3]);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Erro: Argumento(s) invalidos.\n";
        return 1;
    } catch (const std::out_of_range& e) {
        std::cerr << "Erro: Argumento esta fora do intervalo de representcao de int.\n";
        return 1;
    }

    std::unordered_map<std::string, int> hashTable = createHashTable();

    if(!(hashTable.find(caseArgument) != hashTable.end())){
        std::cout << "O primeiro argumento precisa ser um destes: ['-a', '-b', '-w']";
        return 1;
    }
    
    std::vector<std::string> tableHead = {"Qtd. comparacoes", "Qtd. trocas", "Tempo Execucao"};

    std::vector<std::vector<double>> tableBody = {{},{},{}};

    //Executa o Heap sort N vezes baseado no argumento passado na execução
    for(int j = 0; j < timesSamples; j++){
        //Inicia a estrutura para contar as comparações e operações
        struct Counters counters;
        //Cria um vetor baseado no paramêtro de entrada, crescente, decrescente, aleatório e a quantidade
        std::vector<int> array = createVector(hashTable[caseArgument], arraySizeArgument);
        //Inicia a contagem de tempo
        auto start_time = std::chrono::high_resolution_clock::now();
        //Realiza o Heap Sort
        heap_sort(array, counters);
        //Para de contar tempo
        auto end_time = std::chrono::high_resolution_clock::now();
        //Calcula quanto tempo passou
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        //Converte o tempo para segungos
        double seconds = duration.count() / 1e6;
        //Insere nos arrays a contagem de compárações, operações e tempo
        tableBody[0].push_back(counters.comparisons);
        tableBody[1].push_back(counters.operations);
        tableBody[2].push_back(seconds);
    }
    
    generateTable(tableHead, tableBody);
    return 0;
}



/*     
        ---------------------COMENTÁRIO MELHORIA----------------------------

    Existem diversas variantes do Heap Sort, a ideia é conseguir ordenar a Heap de forma 
    mais eficiente com outros métodos que envolvam menos comparações. A pagina do Heap sort no wikipedia 
    cita diversos métodos alternativos e variantes do Heap Sort. 

    Ternary Heapsort: Em vez de usar uma heap binária, o Ternary Heapsort utiliza uma heap ternária, 
    na qual cada elemento da heap tem três filhos em vez de dois. Isso reduz o número total de comparações e 
    trocas em relação à heap binária.

    Smoothsort: Smoothsort é uma variação do Heapsort desenvolvida por Edsger W. Dijkstra que tende a ser 
    mais eficiente do que o Heapsort quando a entrada já está parcialmente ordenada. No entanto, devido à sua 
    complexidade, é raramente usado.

    Variantes com poucas comparações: Existem variantes, como weak heapsort e Katajainen's "ultimate heapsort," 
    que realizam um número mínimo de comparações (n log₂ n + O(1)) no pior caso. Essas variantes podem ser úteis 
    quando as comparações são caras, mas podem ser mais complexas de implementar.
*/