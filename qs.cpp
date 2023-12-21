#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>
#include <sstream>
#include <algorithm>

using namespace std;

// algoritmo k-ésimo mínimo que encontra o elemento da mediana em tempo linear
int kEsimoMinimoEncontraMediana(std::vector<int>& array, int inicio, int fim, int k) {
    if (inicio == fim)
        return inicio;

    int pivotIndex = inicio + (fim - inicio) / 2; //inicio + rand() % (fim - inicio + 1);
    int pivot = array[pivotIndex];

    swap(array[pivotIndex], array[fim]);

    // Particionamento
    int i = inicio;
    for (int j = inicio; j < fim; j++) {
        if (array[j] <= pivot) {
            swap(array[i], array[j]);
            i++;
        }
    }

    swap(array[i], array[fim]);

    // Verificar a posição do pivô
    int posicaoPivo = i - inicio + 1;

    if (posicaoPivo == k)
        return i;
    else if (posicaoPivo < k)
        return kEsimoMinimoEncontraMediana(array, i + 1, fim, k - posicaoPivo);
    else
        return kEsimoMinimoEncontraMediana(array, inicio, i - 1, k);
}

//função para selecionar qual metodo de seleção de pivo vai ser utilizado
int getPivotPosition(vector<int> &array, int low, int high, int Pivot_Selection) {
    //pivo fixo no primeiro elemento
    if(Pivot_Selection==1){
        cout << "OK " << low << endl;
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
        return low + rand() % (high - low + 1);
    }

    // pivo mediana usando o Algoritmo Kesimo Mínimo
    if(Pivot_Selection==7){
         int k = (high + 1) / 2; // índice da mediana em um conjunto ímpar
        return kEsimoMinimoEncontraMediana(array, low, high, k);
    }

    // pivos mediana de k valores
    if(Pivot_Selection==5){
        int meio = (low + high) / 2;

        // Ordena os três valores: arr[inicio], arr[meio] e arr[fim]
        if (array[low] > array[meio])
            std::swap(array[low], array[meio]);
        if (array[meio] > array[high])
            std::swap(array[meio], array[high]);
        if (array[low] > array[meio])
            std::swap(array[low], array[meio]);

        // Coloca o valor do meio como pivô
        return meio;
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

// Função de impressão de um array
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

vector<int> creatArrayReturn(int n) {
    vector<int> array;
    for (int i=0;i<n;i++) {
        array.push_back(i+1);
    }
    return array;
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




// Chamada Recursiva para Nova versão do Quick Sort
void quickSortRec(vector<int> &vect, int ini, int fim) {
    int i, j;
    i = ini;
    j = fim - 1;
    int pivo = ini;// getPivotPosition(vect, ini, fim, 1); //vect[(ini + fim) / 2];

    ///Inicio Particionamento
    while (i <= j) {
        while (vect[i] < pivo && i < fim) {
            i++;
        }
        while (vect[j] > pivo && j > ini) {
            j--;
        }
        if (i <= j) {
            int aux = vect[i];
            vect[i] = vect[j];
            vect[j] = aux;
            i++;
            j--;
        }
    }
    ///Fim Particionamento

    ///Chamadas recursivas
    if (j > ini)
        quickSortRec(vect, ini, j + 1);
    if (i < fim)
        quickSortRec(vect, i, fim);
}

// Chamada principal para nova versão do QuickSort
void quickSortNewVersion(vector<int> &vect)
{
    quickSortRec(vect, 0, vect.size());
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



    // for(p = 0;p<5;p++){
    string pivotamento = to_string(Pivot_Selection);
    string tamanho = to_string(size[p]);
    string saida = "data_" +  pivotamento + "_" + tamanho  + ".txt";
    ofstream arquivo_saida(saida);


    for(float percentSwap: percentSwapArray)
    {
        for(int i=0;i<10;i++){

            cout << "terminando " << i << endl;
            arquivo_saida << "tamanho " << size[p] << " teste: " << i+1 << endl << endl;

            swapingNumbers(array[p], percentSwap);

            auto start_time = chrono::steady_clock::now();
            if(Pivot_Selection == 1) {
                quickSortNewVersion(array[p]);
            }
            else {
                quickSort(array[p], 0, size[p] - 1,Pivot_Selection);
            }
            auto end_time = chrono::steady_clock::now();

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