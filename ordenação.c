#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 100000000 // mudo o tamanho aqui
#define TEMPO_LIMITE 300000

void bubbleSort(int v[], int n);
void insertionSort(int v[], int n);
void selectionSort(int v[], int n);
void NumerosAleatorios(int v[], int tam);
void OrdemCrescente(int v[], int tam);
void OrdemDecrescente(int v[], int tam);
double medirTempo(void (*funcoes)(int*, int), int *v, int tam);

int main(){
    int tamanho = TAM;
    int *v = (int *)malloc(tamanho * sizeof(int));

    if(v == NULL){
        printf("Falha na alocação da memoria!\n");
        return 1;
    }

    void (*algoritmos[])(int*, int) = {bubbleSort, insertionSort, selectionSort};
    const char *nomes[] = {"Bubble Sort", "Insertion Sort", "Selection Sort"};

    for(int i = 0; i < 3; i++){
        printf("Executando %s...\n", nomes[i]);
        for (int j = 0; j < 3; j++) {
            
            if (j == 0) {
                NumerosAleatorios(v, tamanho);
                printf("Vetor desordenado: ");
            } else if (j == 1) {
                OrdemCrescente(v, tamanho);
                printf("Vetor ordenado crescente: ");
            } else {
                OrdemDecrescente(v, tamanho);
                printf("Vetor ordenado decrescente: ");
            }

            double tempoExecucao;
            while (1) {
                tempoExecucao = medirTempo(algoritmos[i], v, tamanho);

                if (tempoExecucao <= TEMPO_LIMITE) {
                    printf("Tempo de execução para tamanho %d: %.2f ms\n", tamanho, tempoExecucao);
                    break;
                } else {
                    printf("Tempo excedido para tamanho %d: %.2f ms. Reduzindo o tamanho pela metade.\n", tamanho, tempoExecucao);
                    tamanho /= 2;

                    if (tamanho <= 0) {
                        printf("Tamanho do vetor reduzido a zero, encerrando.\n");
                        break;
                    }

                    v = (int *)realloc(v, tamanho * sizeof(int));
                    if (v == NULL) {
                        printf("Erro ao realocar memória.\n");
                        return 1;
                    }
                }
            }
        }
        printf("\n");
    }

    free(v);
    return 0;
}

void bubbleSort(int v[], int n){
    int temp;
    for(int i = 1; i < n; i++){
        for(int j = 0; j < n - i; j++){
            if(v[j] > v[j + 1]){
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

void insertionSort(int v[], int n){
    for(int i = 1; i < n; i++){
        int chave = v[i];
        int j = i - 1;
        while(j >= 0 && v[j] > chave){
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}

void selectionSort(int v[], int n){
    for(int i = 0; i < n - 1; i++){
        int idcMin = i;
        for(int j = i + 1; j < n; j++){
            if(v[j] < v[idcMin]){
                idcMin = j;
            }
        }
        if(idcMin != i){
            int temp = v[i];
            v[i] = v[idcMin];
            v[idcMin] = temp;
        }
    }
}

void NumerosAleatorios(int v[], int tam){
    for(int i = 0; i < tam; i++){
        v[i] = rand() % 10000;
    }
}

void OrdemCrescente(int v[], int tam){
    for(int i = 0; i < tam; i++){
        v[i] = i;
    }
}

void OrdemDecrescente(int v[], int tam){
    for(int i = 0; i < tam; i++){
        v[i] = tam - i - 1;
    }
}

double medirTempo(void (*funcoes)(int*, int), int *v, int tam){
    clock_t inicio = clock();
    funcoes(v,tam);
    clock_t fim = clock();
    return ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000;
}
