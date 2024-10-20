#include <stdio.h>
#include <string.h>
#include <math.h>
#define TAM_NOME 50

struct Pessoa{
    char nome[TAM_NOME];
    int idade;
    double altura, peso;
};

void lerstr(char *str, int tam);
void lerPessoa(struct Pessoa *pessoa);
void imprimirPessoa(struct Pessoa pessoa);
double calculaIMC(struct Pessoa pessoa);
void imprimeInterpretacaoIMC(double imc);

int main(){
    struct Pessoa pessoa;
    char continuar;
    do{
        lerPessoa(&pessoa);
        printf("\nPESSOA\n\n");

        imprimirPessoa(pessoa);
        double imc = calculaIMC(pessoa);
        printf("\nO seu IMC é: %.1f\n", imc);
        imprimeInterpretacaoIMC(imc);
        printf("\nDeseja calcular o IMC de outra pessoa? (s/n): ");
        scanf(" %c", &continuar);

    }while(continuar == 's' || continuar == 'S');

    printf("\nPrograma encerrado.\n");

    return 0;
}

void lerstr(char *str, int tam){
    fgets(str, tam, stdin);
    int len = strlen(str);
    if(str[len - 1] == '\n'){
        str[len - 1] = '\0';
    }
}

void lerPessoa(struct Pessoa *pessoa){
    printf("Digite seu nome: ");
    getchar();  
    lerstr(pessoa->nome, TAM_NOME);
    
    printf("Digite sua idade: ");
    scanf("%d", &pessoa->idade);
    
    printf("Digite sua altura: ");
    scanf("%lf", &pessoa->altura);
    
    printf("Digite seu peso: ");
    scanf("%lf", &pessoa->peso);
}

void imprimirPessoa(struct Pessoa pessoa){
    printf("Nome: %s\n", pessoa.nome);
    printf("Idade: %d\n", pessoa.idade);
    printf("Altura: %.2f\n", pessoa.altura);
    printf("Peso: %.2f\n", pessoa.peso);
}

double calculaIMC(struct Pessoa pessoa){
    return pessoa.peso / pow(pessoa.altura, 2);
}

void imprimeInterpretacaoIMC(double imc){
    char classificacao[20];
    if(imc < 18.5){
        strcpy(classificacao, "Magreza");
    }else if(imc < 25.0){
        strcpy(classificacao, "Normal");
    }else if(imc < 30.0){
        strcpy(classificacao, "Sobrepeso");
    }else if(imc < 40.0){
        strcpy(classificacao, "Obesidade");
    }else{
        strcpy(classificacao, "Obesidade grave");
    }
    printf("Classificação: %s\n", classificacao);
}
