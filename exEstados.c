#include <stdio.h>
#include <string.h>
#define TAM_NOME 50
#define N_ESTADOS 2

struct Estado{
    char nome[TAM_NOME];
    int veiculos;
    int acidente;
};

void lerstr(char *str, int tam);
void ColetaDados(struct Estado estados[]);
void imprimeEstado(struct Estado estado);

int main(){

    struct Estado estados[N_ESTADOS];
    ColetaDados(estados);

    for(int i = 0; i < N_ESTADOS; i++){
        printf("\nESTADO\n\n");
        imprimeEstado(estados[i]);
    }
    return 0;
}

void lerstr(char *str, int tam){
    fgets(str, tam, stdin);
    int len = strlen(str);
    if(str[len - 1] == '\n'){
        str[len - 1] = '\0';
    }
}

void ColetaDados(struct Estado estados[]){
    for(int i = 0; i < N_ESTADOS; i++){
        printf("Digite o nome do %dº estado: ", i + 1);
        lerstr(estados[i].nome, TAM_NOME);
        printf("Digite o número de veículos: ");
        scanf("%d", &estados[i].veiculos);
        printf("Digite o número de acidentes: ");
        scanf("%d", &estados[i].acidente);
        getchar();
        printf("\n\n");
    }
}

void imprimeEstado(struct Estado estado){
    printf("Estado: %s\n", estado.nome);
    printf("Número de veículos: %d\n", estado.veiculos);
    printf("Número de acidentes: %d\n", estado.acidente);
}
