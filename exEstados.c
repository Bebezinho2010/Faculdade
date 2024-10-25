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
void encontraMaiorMenorAcidente(struct Estado estados[], int *indiceMaior, int *indiceMenor);
double PercentualAcidente(struct Estado estado);
double CalculaMediaAcidente(struct Estado estados[]);
void EstadosAcimaDaMedia(struct Estado estados[], double media);

int main(){

    struct Estado estados[N_ESTADOS];
    int indiceMaior;
    int indiceMenor;
    ColetaDados(estados);
    encontraMaiorMenorAcidente(estados, &indiceMaior, &indiceMenor);

    for(int i = 0; i < N_ESTADOS; i++){
        printf("\nESTADO\n");
        imprimeEstado(estados[i]);
        double percentual = PercentualAcidente(estados[i]);
        printf("Percentual de veículos envolvidos em acidentes: %.2f%%\n", percentual);
    }

    printf("\nEstado com maior número de acidentes: ");
    imprimeEstado(estados[indiceMaior]);

    printf("\nEstado com menor número de acidentes: ");
    imprimeEstado(estados[indiceMenor]);

    double MediaAcidentes = CalculaMediaAcidente(estados);
    printf("\nMédia de acidentes no país: %.1f\n", MediaAcidentes);

    EstadosAcimaDaMedia(estados, MediaAcidentes);

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

void encontraMaiorMenorAcidente(struct Estado estados[], int *indiceMaior, int *indiceMenor){
    *indiceMaior = 0;
    *indiceMenor = 0;
    for(int i = 1; i < N_ESTADOS; i++){
        if(estados[i].acidente > estados[*indiceMaior].acidente){
            *indiceMaior = i;
        }
        if(estados[i].acidente < estados[*indiceMenor].acidente){
            *indiceMenor = i;
        }
    }
}

double PercentualAcidente(struct Estado estado){
    if(estado.veiculos == 0){
        return 0.0;
    }
    return ((double)estado.acidente/estado.veiculos)*100;
}

double CalculaMediaAcidente(struct Estado estados[]){
    int total = 0;
    for(int i = 0; i < N_ESTADOS; i++){
        total += estados[i].acidente;
    }
    return (double)total / N_ESTADOS;
}

void EstadosAcimaDaMedia(struct Estado estados[], double media){
    printf("\nEstados que estão acima da média de acidentes: ");
    for(int i = 0; i < N_ESTADOS; i++){
        if(estados[i].acidente > media){
            imprimeEstado(estados[i]);
            printf("\n");
        }
    }
}
