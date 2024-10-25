#include <stdio.h>
#include <string.h>
#define PRODUTOS 40
#define MAX 200


struct Produto{
    int codigo;
    char descricao[MAX];
    double valorUnitario;
    int estoque;
};

void lerstr(char *str, int tam);
void cadastraProduto(struct Produto *produtos, int *cont);
void alterarValorUnitário(struct Produto *produtos, int cont, int codigo);
double informarValorUnitario(struct Produto *produtos, int cont, int codigo);
int informarEstoque(struct Produto *produtos, int cont, int codigo);
void venda(struct Produto *produtos, int cont, int codigo, int qtd);

int main(){
    struct Produto produtos[PRODUTOS];
    return 0;
}

void lerstr(char *str, int tam){
    fgets(str, tam, stdin);
    int len = strlen(str);
    if(str[len - 1] == '\n'){
        str[len - 1] = '\0';
    }
}

void cadastraProduto(struct Produto *produtos, int *cont){
    if(*cont >= PRODUTOS){
        printf("Limite atingido.\n");
        return;
    }
    struct Prodruto NovoProduto;
    printf("Cadastro do Produto %d:\n", *cont + 1);
    printf("Código: ");
    scanf("%d", &NovoProduto.codigo);
    printf("Descrição do produto: ");
    getchar();
    lerstr(NovoProduto.descricao, MAX);
    printf("Valor unitário: ");
    scanf("%lf", &NovoProduto.valorUnitario);
    printf("Quantidade em estoque: ");
    scanf("%d", &NovoProduto.estoque);

    produtos[*cont] = NovoProduto;
    (*cont)++;
    printf("Produto cadastrado com sucesso!\n");
}

void alterarValorUnitário(struct Produto *produtos, int cont, int codigo){
    for(int i = 0; i < cont; i++){
        if(produtos[i].codigo == codigo){
            printf("Digite um novo valor unitário para o produto de codigo %d: ", codigo);
            scanf("%lf", &produtos[i].valorUnitario);
            printf("Valor unitário alterado.\n");
            return;
        }
    }
    printf("Produto não encontrado.\n");
}

double informarValorUnitario(struct Produto *produtos, int cont, int codigo){
    for(int i = 0; i < cont; i++){
        if(produtos[i].codigo == codigo){
            return produtos[i].valorUnitario;
        }
    }
    return -1;
}

int informarEstoque(struct Produto *produtos, int cont, int codigo){
    for(int i = 0; i < cont; i++){
        if(produtos[i].codigo == codigo){
            return produtos[i].estoque;
        }
    }
    return -1;
}

void venda(struct Produto *produtos, int cont, int codigo, int qtd){
    char confirmacao;
    double total;
    for(int i = 0; i < cont; i++){
        if(produtos[i].codigo == codigo){
            if(produtos[i].estoque == 0){
                printf("Produto fora de estoque.\n");
                return;
            }
            if(qtd > produtos[i].estoque){
                printf("Estoque cheio.\n");
                printf("Deseja efetivar a compra e zerar o estoque ?(s para sim, qualquer outra tecla para não: )");
                getchar();
                scanf("%c", &confirmacao);
                if(confirmacao == 's' || confirmacao == 'S'){
                    total = produtos[i].estoque * produtos[i].valorUnitario;
                    produtos[i].estoque = 0;
                    printf("Compra realizada. Valor total: R$ %.2f\n", total);
                }else{
                    printf("Venda cancelada.\n");
                }
            }else{
                total = qtd * produtos[i].valorUnitario;
                produtos[i].estoque -= qtd;
                printf("Venda realizada. Valor total: R$ %.2f\n", total);
            }
            return;
        }
    }
    printf("Produto não encontrado.\n");
}
