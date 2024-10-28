#include <stdio.h>
#include <string.h>
#define MAX_CONTA 5
#define TAM_NOME 100
#define TAM_CPF 12
#define TAM_TELEFONE 15

struct Conta {
    int numeroConta;
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char telefone[TAM_TELEFONE];
    double saldo;
};

void lerstr(char *str, int tam);
int busca(struct Conta contas[], int total, int numero);
void cadastrarConta(struct Conta contas[], int *total, int numeroNovo);
void consultarSaldo(struct Conta contas[], int total, int numeroConta);
void depositar(struct Conta contas[], int total, int numeroConta);
void sacar(struct Conta contas[], int total, int numeroConta);
void exibirContas(struct Conta contas[], int total);

int main() {
    struct Conta contas[MAX_CONTA];
    int totalContas = 0;
    int opcao, numeroConta;

    do {
        printf("\nMenu:\n");
        printf("Digite 1 para cadastrar uma conta.\n");
        printf("Digite 2 para consultar o saldo.\n");
        printf("Digite 3 para fazer um depósito.\n");
        printf("Digite 4 para sacar um valor.\n");
        printf("Digite 5 para exibir contas cadastradas.\n");
        printf("Digite 6 para sair.\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Digite o número da nova conta: ");
                scanf("%d", &numeroConta);
                cadastrarConta(contas, &totalContas, numeroConta);
                break;
            case 2:
                printf("Digite o número da conta: ");
                scanf("%d", &numeroConta);
                consultarSaldo(contas, totalContas, numeroConta);
                break;
            case 3:
                printf("Digite o número da conta: ");
                scanf("%d", &numeroConta);
                depositar(contas, totalContas, numeroConta);
                break;
            case 4:
                printf("Digite o número da conta: ");
                scanf("%d", &numeroConta);
                sacar(contas, totalContas, numeroConta);
                break;
            case 5:
                exibirContas(contas, totalContas);
                break;
            case 6:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 6);
    return 0;
}

void lerstr(char *str, int tam) {
    fgets(str, tam, stdin);
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int busca(struct Conta contas[], int total, int numero) {
    if (total == 0) {
        return -1;
    }
    int esquerda = 0, direita = total - 1, meio;
    while (esquerda <= direita) {
        meio = (esquerda + direita) / 2;
        if (contas[meio].numeroConta == numero) {
            return meio;
        } else if (contas[meio].numeroConta < numero) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return -2;
}

void cadastrarConta(struct Conta contas[], int *total, int numeroNovo) {
    if (*total >= MAX_CONTA) {
        printf("Limite máximo de contas atingido.\n");
        return;
    }

    int posicao = busca(contas, *total, numeroNovo);
    if (posicao >= 0) {
        printf("Não foi possível cadastrar. Número de conta repetido.\n");
        return;
    }

    int i = *total - 1;
    while (i >= 0 && contas[i].numeroConta > numeroNovo) {
        contas[i + 1] = contas[i];
        i--;
    }

    contas[i + 1].numeroConta = numeroNovo;

    printf("Digite o nome do cliente: ");
    lerstr(contas[i + 1].nome, TAM_NOME);

    printf("Digite o CPF do cliente: ");
    lerstr(contas[i + 1].cpf, TAM_CPF);

    printf("Digite o telefone do cliente: ");
    lerstr(contas[i + 1].telefone, TAM_TELEFONE);

    printf("Digite o saldo inicial: ");
    scanf("%lf", &contas[i + 1].saldo); 
    getchar();

    (*total)++;
    printf("Conta cadastrada com sucesso!\n");
}

void consultarSaldo(struct Conta contas[], int total, int numeroConta) {
    int posicao = busca(contas, total, numeroConta);
    
    if (posicao >= 0) {
        printf("Saldo da conta %d: R$ %.2lf\n", contas[posicao].numeroConta, contas[posicao].saldo);
    } else {
        printf("Conta não cadastrada.\n");
    }
}

void depositar(struct Conta contas[], int total, int numeroConta) {
    int posicao = busca(contas, total, numeroConta);
    
    if (posicao >= 0) {
        double valorDeposito;
        printf("Digite o valor do depósito: R$ ");
        scanf("%lf", &valorDeposito);
        contas[posicao].saldo += valorDeposito; 
        printf("Depósito de R$ %.2lf realizado com sucesso na conta %d.\n", valorDeposito, numeroConta);
    } else {
        printf("Conta não cadastrada.\n");
    }
}

void sacar(struct Conta contas[], int total, int numeroConta) {
    int posicao = busca(contas, total, numeroConta);
    
    if (posicao >= 0) {
        double valorSaque;
        printf("Digite o valor do saque: R$ ");
        scanf("%lf", &valorSaque);

        if (valorSaque <= contas[posicao].saldo) {
            contas[posicao].saldo -= valorSaque; 
            printf("Saque de R$ %.2lf realizado com sucesso na conta %d.\n", valorSaque, numeroConta);
        } else {
            printf("Não existe saldo suficiente para realizar o saque.\n");
        }
    } else {
        printf("Conta não cadastrada.\n");
    }
}

void exibirContas(struct Conta contas[], int total) {
    if (total == 0) {
        printf("Nenhuma conta cadastrada.\n");
        return;
    }

    printf("Contas cadastradas:\n");
    for (int i = 0; i < total; i++) {
        printf("Número da Conta: %d\n", contas[i].numeroConta);
        printf("Nome do Titular: %s\n", contas[i].nome);
        printf("Telefone: %s\n", contas[i].telefone);
        printf("------------------------------\n"); 
    }
}
