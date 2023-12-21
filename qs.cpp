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
int getPivotPosition(vector<int> &array, int ini, int fim, int pivoSelectOption) {
    //pivo fixo no primeiro elemento
    if(pivoSelectOption==1){
        cout << "OK " << ini << endl;
        return ini;
    }

    //Pivô fixo na posição central da lista
    if(pivoSelectOption==2){
        return ini + (fim - ini) / 2;
    }

    //Pivô média considerando a média do primeiro , central e último valores da lista
    if(pivoSelectOption==3){
        //return ((ini + (fim - ini) / 2)+ini+fim)/3;
            int meio = (ini + fim) / 2;
            int indiceMaisProximo = fim;

            // Calcula a média dos valores do início, meio e fim
            int media = (array[ini] + array[meio] + array[fim]) / 3;
            int diferencaMaisProxima = abs(array[ini] - media);

            for (int i = ini + 1; i <= fim; ++i) {
                int diferencaAtual = abs(array[i] - media);
                if (diferencaAtual < diferencaMaisProxima) {
                    diferencaMaisProxima = diferencaAtual;
                    indiceMaisProximo = i;
                }
            }


    return indiceMaisProximo;
    }


    //gera pivos aleatorios
    if(pivoSelectOption==4){
        return ini + rand() % (fim - ini + 1);
    }

    // pivo mediana usando o Algoritmo Kesimo Mínimo
    if(pivoSelectOption==7){
         int k = (fim + 1) / 2; // índice da mediana em um conjunto ímpar
        return kEsimoMinimoEncontraMediana(array, ini, fim, k);
    }

    // pivos mediana de k valores
    if(pivoSelectOption==5){
        int meio = (ini + fim) / 2;

        // Ordena os três valores: arr[inicio], arr[meio] e arr[fim]
        if (array[ini] > array[meio])
            std::swap(array[ini], array[meio]);
        if (array[meio] > array[fim])
            std::swap(array[meio], array[fim]);
        if (array[ini] > array[meio])
            std::swap(array[ini], array[meio]);

        // Coloca o valor do meio como pivô
        return meio;
    }


     //gera pivos utilizando o metodo de "acha pivo"
    if(pivoSelectOption==6){
        int mid = ini + (fim - ini) / 2;
        int pivotIndex = mid;

        if ((array[ini] <= array[mid] && array[mid] <= array[fim]) ||
            (array[fim] <= array[mid] && array[mid] <= array[ini])) {
            pivotIndex = mid;
        } else if ((array[mid] <= array[ini] && array[ini] <= array[fim]) ||
                   (array[fim] <= array[ini] && array[ini] <= array[mid])) {
            pivotIndex = ini;
        } else {
            pivotIndex = fim;
        }

    return pivotIndex;
    }


    return 0;

}

// Função de partição do QuickSort
int partition(vector<int>& array, int ini, int fim, int pivoSelectOption) {
    int pivotIndex = getPivotPosition(array, ini, fim, pivoSelectOption);
    swap(array[pivotIndex], array[fim]);


    int pivot = array[fim]; // Pivô é agora o último elemento
    int i = ini - 1; // Índice do menor elemento

    for (int j = ini; j < fim; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(array[i], array[j]);
        }
    }

    swap(array[i + 1], array[fim]);
    return i + 1;
}

// Função principal do QuickSort
void quickSort(vector<int>& array, int ini, int fim, int pivoSelectOption) {
    if (ini < fim) {
        int pi = partition(array, ini, fim, pivoSelectOption);
        quickSort(array, ini, pi - 1, pivoSelectOption);
        quickSort(array, pi + 1, fim, pivoSelectOption);
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
    int pivoSelectOption = 1;
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
    string pivotamento = to_string(pivoSelectOption);
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
            if(pivoSelectOption == 1) {
                quickSortNewVersion(array[p]);
            }
            else {
                quickSort(array[p], 0, size[p] - 1,pivoSelectOption);
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