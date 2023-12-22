#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>
#include <sstream>
#include <algorithm>


// Este código analisa o desempenho do algoritmo QuickSort sob diferentes condições, como diferentes métodos de seleção de pivôs e níveis de desorganização do vect

using namespace std;


// Função de impressão de um vect
void printArray(const vector<int>& vect) {
    for (int value : vect) {
        cout << value << " ";
    }
    cout << endl;
}

void createArray(vector<int>& vect,int n) {
    for (int i=0;i<n;i++) {
        vect.push_back(i+1);
    }
}

vector<int> creatArrayReturn(int n) {
    vector<int> vect;
    for (int i=0;i<n;i++) {
        vect.push_back(i+1);
    }
    return vect;
}

void swapingNumbers(vector<int> &vect, float swapProportion) {
    int size = vect.size();
    float numSwap = size * swapProportion;

    for (int i = 0; i < numSwap; ++i) {

        int indice1 = rand() % size;
        int indice2 = rand() % size;

        swap(vect[indice1], vect[indice2]);
    }
}



// algoritmo k-ésimo mínimo que encontra o elemento da mediana em tempo linear
int kEsimoMinimoEncontraMediana(std::vector<int>& vect, int inicio, int fim, int k) {
    if (inicio == fim)
        return inicio;

    int pivotIndex = inicio + (fim - inicio) / 2; //inicio + rand() % (fim - inicio + 1);
    int pivot = vect[pivotIndex];

    swap(vect[pivotIndex], vect[fim]);

    // Particionamento
    int i = inicio;
    for (int j = inicio; j < fim; j++) {
        if (vect[j] <= pivot) {
            swap(vect[i], vect[j]);
            i++;
        }
    }

    swap(vect[i], vect[fim]);

    // Verificar a posição do pivô
    int posicaoPivo = i - inicio + 1;

    if (posicaoPivo == k)
        return i;
    else if (posicaoPivo < k)
        return kEsimoMinimoEncontraMediana(vect, i + 1, fim, k - posicaoPivo);
    else
        return kEsimoMinimoEncontraMediana(vect, inicio, i - 1, k);
}

int encontrarMenorValorIndice(vector<int> &vect) {

    int tamanho = vect.size();

    if (tamanho <= 0) {
        // Retorna -1 se o vect estiver vazio
        return -1;
    }

    int menorValor = vect[0];
    int indiceMenorValor = 0;

    for (int i = 1; i < tamanho; ++i) {
        if (vect[i] < menorValor) {
            menorValor = vect[i];
            indiceMenorValor = i;
        }
    }

    return indiceMenorValor;
}


int achaPivo(vector<int>& vect, int ini, int fim) {
    int pivo = 0;
    int pos = ini + 1;

    while (pos <= fim) {
        if (vect[pos] >= vect[pos - 1]) {
            pos += 1;
        } else {
            pivo = pos;
            pos = fim + 1;
        }
    }

    return pivo;
}


//função para selecionar qual metodo de seleção de pivo vai ser utilizado
int getPivotPosition(vector<int> &vect, int ini, int fim, int pivoSelectOption) {
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
            int media = (vect[ini] + vect[meio] + vect[fim]) / 3;
            int diferencaMaisProxima = abs(vect[ini] - media);

            for (int i = ini + 1; i <= fim; ++i) {
                int diferencaAtual = abs(vect[i] - media);
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
        return kEsimoMinimoEncontraMediana(vect, ini, fim, k);
    }




     //gera pivos utilizando o metodo de "acha pivo"
    if(pivoSelectOption==6){
        return achaPivo(vect, ini, fim);
    }


    //pivo encontrado sendo o menor valor do vetor
    if(pivoSelectOption==7){
        return encontrarMenorValorIndice(vect);//ini;
    }

    // pivos mediana de k valores - no caso fizemos para k=3
    int k = 3;
    if(pivoSelectOption==8){
        int meio = (ini + fim) / 2;

        // Ordena os três valores: arr[inicio], arr[meio] e arr[fim]
        if (vect[ini] > vect[meio])
            std::swap(vect[ini], vect[meio]);
        if (vect[meio] > vect[fim])
            std::swap(vect[meio], vect[fim]);
        if (vect[ini] > vect[meio])
            std::swap(vect[ini], vect[meio]);

        // Coloca o valor do meio como pivô
        return meio;
    }

    //gera pivos utilizando o metodo de "acha pivo" encontrado na internet
    if(pivoSelectOption==9){
        int mid = ini + (fim - ini) / 2;
        int pivotIndex = mid;

        if ((vect[ini] <= vect[mid] && vect[mid] <= vect[fim]) ||
            (vect[fim] <= vect[mid] && vect[mid] <= vect[ini])) {
            pivotIndex = mid;
        } else if ((vect[mid] <= vect[ini] && vect[ini] <= vect[fim]) ||
                   (vect[fim] <= vect[ini] && vect[ini] <= vect[mid])) {
            pivotIndex = ini;
        } else {
            pivotIndex = fim;
        }

    return pivotIndex;
    }

    return 0;

}

// Função de partição do QuickSort
int partition(vector<int>& vect, int ini, int fim, int pivoSelectOption) {
    int pivotIndex = getPivotPosition(vect, ini, fim, pivoSelectOption);
    swap(vect[pivotIndex], vect[fim]);


    int pivot = vect[fim]; // Pivô é agora o último elemento
    int i = ini - 1; // Índice do menor elemento

    for (int j = ini; j < fim; j++) {
        if (vect[j] <= pivot) {
            i++;
            swap(vect[i], vect[j]);
        }
    }

    swap(vect[i + 1], vect[fim]);
    return i + 1;
}

// Função principal do QuickSort
void quickSort(vector<int>& vect, int ini, int fim, int pivoSelectOption) {
    if (ini < fim) {
        int pi = partition(vect, ini, fim, pivoSelectOption);
        quickSort(vect, ini, pi - 1, pivoSelectOption);
        quickSort(vect, pi + 1, fim, pivoSelectOption);
    }
}

// Chamada Recursiva para Nova versão do Quick Sort com pivo sendo primeiro elemento
void quickSortRec(vector<int> &vect, int ini, int fim) {
    int i, j;
    i = ini;
    j = fim - 1;
    int pivo = ini;

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




/*

- `pivoSelectOption` controla o método de seleção de pivô.
- `p` é usado para iterar através do vect `size`.
- `percentSwapArray` contém os níveis de desorganização.
-  vect `size` contém os tamanhos dos arrays a serem classificados.
- `vect` é uma matriz de vetores, cada vect representando uma matriz de inteiros de um tamanho específico.

*/

int main() {




    srand(time(0));
    int pivoSelectOption = 6;
    int p = 0;

    float percentSwapArray[3] = {0.05, 0.25, 0.45};

    int size[5];

    size[0] = 100;
    size[1] = 1000;
    size[2] = 10000;
    size[3] = 100000;
    size[4] = 1000000;

    vector<int> vect[5];
    for(int i = 0;i<5;i++){
        createArray(vect[i],size[i]);
    }


    string pivotamento = to_string(pivoSelectOption);
    string tamanho = to_string(size[p]);
    string saida = "data_" +  pivotamento + "_" + tamanho  + ".txt";
    ofstream arquivo_saida(saida);


    for(float percentSwap: percentSwapArray)
    {
        for(int i=0;i<10;i++){

            cout << "terminando " << i << endl;
            arquivo_saida << "tamanho " << size[p] << " teste: " << i+1 << endl << endl;

            swapingNumbers(vect[p], percentSwap);

            auto start_time = chrono::steady_clock::now();
            if(pivoSelectOption == 1) {
                quickSortNewVersion(vect[p]);
            }
            else {
                quickSort(vect[p], 0, size[p] - 1,pivoSelectOption);
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