#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>
#include <sstream>
#include <algorithm>

using namespace std;
//função para selecionar qual metodo de seleção de pivo vai ser utilizado
int getPivotPosition(vector<int>& array, int low, int high, int Pivot_Selection) {
    //pivo fixo no primeiro elemento
    if(Pivot_Selection==1){
        return low;
    }

    //Pivô fixo na posição central da lista
    if(Pivot_Selection==2){
        return low + (high - low) / 2;
    }

    //Pivô média considerando a média do primeiro , central e último valores da lista
    if(Pivot_Selection==3){
        //return ((low + (high - low) / 2)+low+high)/3;
            int meio = (low + high) / 2;
            int indiceMaisProximo = high;

            // Calcula a média dos valores do início, meio e fim
            int media = (array[low] + array[meio] + array[high]) / 3;
            int diferencaMaisProxima = abs(array[low] - media);

            for (int i = low + 1; i <= high; ++i) {
                int diferencaAtual = abs(array[i] - media);
                if (diferencaAtual < diferencaMaisProxima) {
                    diferencaMaisProxima = diferencaAtual;
                    indiceMaisProximo = i;
                }
            }

    return indiceMaisProximo;
    }

    //gera pivos aleatorios
    if(Pivot_Selection==4){
        int meio = (low + high) / 2;
        vector<int> pivoMediana = {array[low], array[meio], array[high]};
        sort(pivoMediana.begin(), pivoMediana.end());
        return pivoMediana[1];
    }

    // pivos mediana de k valores

    if(Pivot_Selection==5){
        int k = 3;

        return low + (high - low) / 2;
    }

     //gera pivos utilizando o metodo de "acha pivo"
    if(Pivot_Selection==6){
        int mid = low + (high - low) / 2;
        int pivotIndex = mid;

        if ((array[low] <= array[mid] && array[mid] <= array[high]) ||
            (array[high] <= array[mid] && array[mid] <= array[low])) {
            pivotIndex = mid;
        } else if ((array[mid] <= array[low] && array[low] <= array[high]) ||
                   (array[high] <= array[low] && array[low] <= array[mid])) {
            pivotIndex = low;
        } else {
            pivotIndex = high;
        }

    return pivotIndex;
    }


    return 0;

}

// Função de partição do QuickSort
int partition(vector<int>& array, int low, int high, int Pivot_Selection) {
    int pivotIndex = getPivotPosition(array, low, high, Pivot_Selection);
    swap(array[pivotIndex], array[high]);


    int pivot = array[high]; // Pivô é agora o último elemento
    int i = low - 1; // Índice do menor elemento

    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(array[i], array[j]);
        }
    }

    swap(array[i + 1], array[high]);
    return i + 1;
}

// Função principal do QuickSort
void quickSort(vector<int>& array, int low, int high, int Pivot_Selection) {
    if (low < high) {
        int pi = partition(array, low, high, Pivot_Selection);
        quickSort(array, low, pi - 1, Pivot_Selection);
        quickSort(array, pi + 1, high, Pivot_Selection);
    }
}

// Função de impressão de um vetor
void printArray(const vector<int>& array) {
    for (int value : array) {
        cout << value << " ";
    }
    cout << endl;
}

void intArray(vector<int>& array,int n) {
    for (int i=0;i<n;i++) {
        array[i]=i+1;
    }
}

void creatArray(vector<int>& array,int n) {
    for (int i=0;i<n;i++) {
        array.push_back(i+1);
    }
}

void swapingNumbers(vector<int> &array, float swapProportion) {
    int size = array.size();
    float numSwap = size * swapProportion;

    for (int i = 0; i < numSwap; ++i) {

        int indice1 = rand() % size;
        int indice2 = rand() % size;

        swap(array[indice1], array[indice2]);
    }
}



int main() {




    srand(time(0));
    int Pivot_Selection = 1;
    int p = 3;

    float percentSwapArray[3] = {0.05, 0.25, 0.45};

    int size[5];

    size[0] = 100;
    size[1] = 1000;
    size[2] = 10000;
    size[3] = 100000;
    size[4] = 1000000;

    vector<int> array[5];
    for(int i = 0;i<5;i++){
        creatArray(array[i],size[i]);
    }

    //printArray(array[p]);


    // for(p = 0;p<5;p++){
    string pivotamento = to_string(Pivot_Selection);
    string tamanho = to_string(size[p]);
    string saida = "data_" +  pivotamento + "_" + tamanho  + ".txt";
    ofstream arquivo_saida(saida);


    for(int i=0;i<10;i++){


        for(auto percentSwap: percentSwapArray)
        {
            cout << "terminando " << i << endl;
            arquivo_saida << "tamanho " << size[p] << " teste: " << i+1 << endl << endl;

            intArray(array[p],size[p]);
            // printArray(array[p]);
            swapingNumbers(array[p], 0.05);
            // printArray(array[p]);

            auto start_time = chrono::steady_clock::now();
            quickSort(array[p], 0, size[p] - 1,Pivot_Selection);
            auto end_time = chrono::steady_clock::now();
            // printArray(array[p]);
            auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

            arquivo_saida << "desorganização nivel: " << int(percentSwap*100) << "% : " << duration.count() << endl;
        }
    }
    arquivo_saida << '\n'<<"-------------------------------------------------------------------------------------------" << '\n';
    arquivo_saida.close();
    // }

    cout << "termino";
    return 0;
}