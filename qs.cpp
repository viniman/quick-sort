#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>
#include <sstream>
#include <algorithm>


// Este código analisa o desempenho do algoritmo QuickSort sob diferentes condições, como diferentes métodos de seleção de pivôs e níveis de desorganização do vectOrder

using namespace std;


// Função de impressão de um vectOrder
void printArray(const vector<int>& vectOrder) {
    for (int value : vectOrder) {
        cout << value << " ";
    }
    cout << endl;
}

void createArray(vector<int>& vectOrder,int n) {
    for (int i=0;i<n;i++) {
        vectOrder.push_back(i+1);
    }
}

vector<int> creatArrayReturn(int n) {
    vector<int> vectOrder;
    for (int i=0;i<n;i++) {
        vectOrder.push_back(i+1);
    }
    return vectOrder;
}

void swapingNumbers(vector<int> &vectOrder, float swapProportion) {
    int size = vectOrder.size();
    float numSwap = size * swapProportion;

    for (int i = 0; i < numSwap; ++i) {

        int indice1 = rand() % size;
        int indice2 = rand() % size;

        swap(vectOrder[indice1], vectOrder[indice2]);
    }
}



// algoritmo k-ésimo mínimo que encontra o elemento da mediana em tempo linear
int kEsimoMinimoEncontraMediana(std::vector<int>& vectOrder, int inicio, int fim, int k) {
    if (inicio == fim)
        return inicio;

    int pivotIndex = inicio + (fim - inicio) / 2; //inicio + rand() % (fim - inicio + 1);
    int pivot = vectOrder[pivotIndex];

    swap(vectOrder[pivotIndex], vectOrder[fim]);

    // Particionamento
    int i = inicio;
    for (int j = inicio; j < fim; j++) {
        if (vectOrder[j] <= pivot) {
            swap(vectOrder[i], vectOrder[j]);
            i++;
        }
    }

    swap(vectOrder[i], vectOrder[fim]);

    // Verificar a posição do pivô
    int posicaoPivo = i - inicio + 1;

    if (posicaoPivo == k)
        return i;
    else if (posicaoPivo < k)
        return kEsimoMinimoEncontraMediana(vectOrder, i + 1, fim, k - posicaoPivo);
    else
        return kEsimoMinimoEncontraMediana(vectOrder, inicio, i - 1, k);
}

int encontrarMenorValorIndice(vector<int> &vectOrder) {

    int tamanho = vectOrder.size();

    if (tamanho <= 0) {
        // Retorna -1 se o vectOrder estiver vazio
        return -1;
    }

    int menorValor = vectOrder[0];
    int indiceMenorValor = 0;

    for (int i = 1; i < tamanho; ++i) {
        if (vectOrder[i] < menorValor) {
            menorValor = vectOrder[i];
            indiceMenorValor = i;
        }
    }

    return indiceMenorValor;
}


int achaPivo(vector<int>& vectOrder, int ini, int fim) {
    int pivo = 0;
    int pos = ini + 1;

    while (pos <= fim) {
        if (vectOrder[pos] >= vectOrder[pos - 1]) {
            pos += 1;
        } else {
            pivo = pos;
            pos = fim + 1;
        }
    }

    return pivo;
}


//função para selecionar qual metodo de seleção de pivo vai ser utilizado
int getPivotPosition(vector<int> &vectOrder, int ini, int fim, int pivoSelectOption) {
    //pivo fixo no primeiro elemento
    if(pivoSelectOption==1){
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
            int media = (vectOrder[ini] + vectOrder[meio] + vectOrder[fim]) / 3;
            int diferencaMaisProxima = abs(vectOrder[ini] - media);

            for (int i = ini + 1; i <= fim; ++i) {
                int diferencaAtual = abs(vectOrder[i] - media);
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
    if(pivoSelectOption==5){
         int k = (fim + 1) / 2; // índice da mediana em um conjunto ímpar
        return kEsimoMinimoEncontraMediana(vectOrder, ini, fim, k);
    }




     //gera pivos utilizando o metodo de "acha pivo"
    if(pivoSelectOption==6){
        return achaPivo(vectOrder, ini, fim);
    }


    //pivo encontrado sendo o menor valor do vetor
    if(pivoSelectOption==7){
        return encontrarMenorValorIndice(vectOrder);//ini;
    }

    // pivos mediana de k valores - no caso fizemos para k=3
    int k = 3;
    if(pivoSelectOption==8){
        int meio = (ini + fim) / 2;

        // Ordena os três valores: arr[inicio], arr[meio] e arr[fim]
        if (vectOrder[ini] > vectOrder[meio])
            std::swap(vectOrder[ini], vectOrder[meio]);
        if (vectOrder[meio] > vectOrder[fim])
            std::swap(vectOrder[meio], vectOrder[fim]);
        if (vectOrder[ini] > vectOrder[meio])
            std::swap(vectOrder[ini], vectOrder[meio]);

        // Coloca o valor do meio como pivô
        return meio;
    }

    //gera pivos utilizando o metodo de "acha pivo" encontrado na internet
    if(pivoSelectOption==9){
        int mid = ini + (fim - ini) / 2;
        int pivotIndex = mid;

        if ((vectOrder[ini] <= vectOrder[mid] && vectOrder[mid] <= vectOrder[fim]) ||
            (vectOrder[fim] <= vectOrder[mid] && vectOrder[mid] <= vectOrder[ini])) {
            pivotIndex = mid;
        } else if ((vectOrder[mid] <= vectOrder[ini] && vectOrder[ini] <= vectOrder[fim]) ||
                   (vectOrder[fim] <= vectOrder[ini] && vectOrder[ini] <= vectOrder[mid])) {
            pivotIndex = ini;
        } else {
            pivotIndex = fim;
        }

    return pivotIndex;
    }

    return 0;

}

// Função de partição do QuickSort
int partition(vector<int>& vectOrder, int ini, int fim, int pivoSelectOption) {
    int pivotIndex = getPivotPosition(vectOrder, ini, fim, pivoSelectOption);
    swap(vectOrder[pivotIndex], vectOrder[fim]);


    int pivot = vectOrder[fim]; // Pivô é agora o último elemento
    int i = ini - 1; // Índice do menor elemento

    for (int j = ini; j < fim; j++) {
        if (vectOrder[j] <= pivot) {
            i++;
            swap(vectOrder[i], vectOrder[j]);
        }
    }

    swap(vectOrder[i + 1], vectOrder[fim]);
    return i + 1;
}

// Função principal do QuickSort
void quickSort(vector<int>& vectOrder, int ini, int fim, int pivoSelectOption) {
    if (ini < fim) {
        int pi = partition(vectOrder, ini, fim, pivoSelectOption);
        quickSort(vectOrder, ini, pi - 1, pivoSelectOption);
        quickSort(vectOrder, pi + 1, fim, pivoSelectOption);
    }
}

// Chamada Recursiva para Nova versão do Quick Sort com pivo sendo primeiro elemento
void quickSortRec(vector<int> &vectOrder, int ini, int fim) {
    int i, j;
    i = ini;
    j = fim - 1;
    int pivo = ini;

    ///Inicio Particionamento
    while (i <= j) {
        while (vectOrder[i] < pivo && i < fim) {
            i++;
        }
        while (vectOrder[j] > pivo && j > ini) {
            j--;
        }
        if (i <= j) {
            int aux = vectOrder[i];
            vectOrder[i] = vectOrder[j];
            vectOrder[j] = aux;
            i++;
            j--;
        }
    }
    ///Fim Particionamento

    ///Chamadas recursivas
    if (j > ini)
        quickSortRec(vectOrder, ini, j + 1);
    if (i < fim)
        quickSortRec(vectOrder, i, fim);
}

// Chamada principal para nova versão do QuickSort
void quickSortNewVersion(vector<int> &vectOrder)
{
    quickSortRec(vectOrder, 0, vectOrder.size());
}




/*

- pivoSelectOption controla o método de seleção de pivô
- positionVectSize é usado para iterar através do vetor vectSize
- percentSwapArray contém os níveis de desorganização
- vetor vectSize contém os tamanhos dos arrays a serem gerados
- vetor é uma matriz de vetores, cada vetor representando uma matriz de inteiros de um tamanho específico

*/

int main() {




    srand(time(0));
    int pivoSelectOption = 6;
    int positionVectSize = 0;

    float percentSwapArray[3] = {0.05, 0.25, 0.45};

    int vectSize[5];

    vectSize[0] = 100;
    vectSize[1] = 1000;
    vectSize[2] = 10000;
    vectSize[3] = 100000;
    vectSize[4] = 1000000;

    vector<int> vectOrder[5];
    for(int i = 0;i<5;i++){
        createArray(vectOrder[i],vectSize[i]);
    }


    string pivotamento = to_string(pivoSelectOption);
    string tamanho = to_string(vectSize[positionVectSize]);
    string saida = "data_" +  pivotamento + "_" + tamanho  + ".txt";
    ofstream arquivo_saida(saida);


    for(float percentSwap: percentSwapArray)
    {
        for(int i=0;i<10;i++){

            cout << "terminando " << i << endl;
            arquivo_saida << "tamanho " << vectSize[positionVectSize] << " teste: " << i+1 << endl << endl;

            swapingNumbers(vectOrder[positionVectSize], percentSwap);

            auto start_time = chrono::steady_clock::now();
            if(pivoSelectOption == 1) {
                quickSortNewVersion(vectOrder[positionVectSize]);
            }
            else {
                quickSort(vectOrder[positionVectSize], 0, vectSize[positionVectSize] - 1,pivoSelectOption);
            }
            auto end_time = chrono::steady_clock::now();

            auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

            arquivo_saida << "desorganização nivel: " << int(percentSwap*100) << "% : " << duration.count() << endl;
        }
    }
    arquivo_saida << '\n'<<"-------------------------------------------------------------------------------------------" << '\n';
    arquivo_saida.close();

    cout << "termino";
    return 0;
}