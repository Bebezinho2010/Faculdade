#include <stdio.h>
#include <math.h>
#include <string.h>
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
    lerPessoa(&pessoa);
    printf("\nPESSOA\n\n");
    imprimirPessoa(pessoa);

    double imc = calculaIMC(pessoa);
    printf("\n o seu IMC é %.1f\n", imc);
    imprimeInterpretacaoIMC(imc);

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
    printf("Digite o seu nome: ");
    lerstr(pessoa->nome, TAM_NOME);
    printf("Digite sua idade: ");
    scanf("%d", &pessoa->idade);
    printf("Digite sua altura: ");
    scanf("%lf", &pessoa->altura);
    printf("Digite seu peso: ");
    scanf("%lf", &pessoa->peso);
}

void imprimirPessoa(struct Pessoa pessoa){
    printf("nome: %s\n", pessoa.nome);
    printf("idade: %d\n", pessoa.idade);
    printf("altura: %f\n", pessoa.altura);
    printf("peso: %f\n", pessoa.peso);
}

double calculaIMC(struct Pessoa pessoa){
    return pessoa.peso / pow(pessoa.altura, 2);
}

void imprimeInterpretacaoIMC(double imc){
    char classificacao[20];
    if(imc < 18.5){
        strcpy(classificacao, "magreza");
    }else if(imc < 25.0){
        strcpy(classificacao, "normal");
    }else if(imc < 30.0){
        strcpy(classificacao, "sobrepeso");
    }else if(imc < 40.0){
        strcpy(classificacao, "obesidade");
    }else{
        strcpy(classificacao, "obesidade grave");
    }
    printf("classificação: %s\n", classificacao);
}
