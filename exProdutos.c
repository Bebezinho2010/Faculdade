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
void atualizarEstoque(struct Produto *produtos, int cont, int codigo, int qtd);
void exibirProduto(struct Produto *produtos, int cont);
void exibirProdutosSemEstoque(struct Produto *produtos, int cont);

int main(){
    struct Produto produtos[PRODUTOS];
    int cont = 0;
    int codigo, qtd, opcao;
    do{
        printf("\nMENU\n");
        printf("Digite 1 para cadastrar um produto.\n");
        printf("Digite 2 para alterar o valor unitário.\n");
        printf("Digite 3 para consultar o valor unitário.\n");
        printf("Digite 4 para consultar o estoque.\n");
        printf("Digite 5 para realizar uma venda.\n");
        printf("Digite 6 para atualizar o estoque.\n");
        printf("Digite 7 para exibir os produtos.\n");
        printf("Digite 8 para exibir produtos sem estoque.\n");
        printf("Digite 9 para sair do programa.\n");
        printf("Digite uma opção: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                cadastraProduto(produtos, &cont);
                break;
            case 2:
                printf("Digite o código do produto para alterar o seu valor unitário: ");
                scanf("%d", &codigo);
                alterarValorUnitário(produtos, cont, codigo);
                break;
            case 3:
                printf("Digite o código do produto para consultar o valor unitário: ");
                scanf("%d", &codigo);
                double valor = informarValorUnitario(produtos, cont, codigo);
                if(valor != -1){
                    printf("O valor unitário do produto é: %.2f\n", valor);
                }else{
                    printf("Produto não encontrado.\n");
                }
                break;
            case 4:
                printf("Digite o código do produto para consultar estoque: ");
                scanf("%d", &codigo);
                int qtdEstoque = informarEstoque(produtos, cont, codigo);
                if(qtdEstoque != -1){
                    printf("A quantidade em estoque do produto é: %d\n", qtdEstoque);
                }else{
                    printf("Produto não encontrado.\n");
                }
                break;
            case 5:
                printf("Digite o código do produto para a venda: ");
                scanf("%d", &codigo);
                printf("Digite a quantidade desejada: ");
                scanf("%d", &qtd);
                venda(produtos, cont, codigo, qtd);
                break;
            case 6:
                printf("Digite o código do produto para atualizar a quantidade em estoque: ");
                scanf("%d", &codigo);
                printf("Digite a nova quantidade em estoque: ");
                scanf("%d", &qtd);
                atualizarEstoque(produtos, cont, codigo, qtd);
                break;
            case 7:
                exibirProduto(produtos, cont);
                break;
            case 8:
                exibirProdutosSemEstoque(produtos, cont);
                break;
            case 9:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Digite novamente.\n");
        }

    }while(opcao != 9);
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
    struct Produto NovoProduto;
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

void atualizarEstoque(struct Produto *produtos, int cont, int codigo, int qtd){
    for(int i = 0; i < cont; i++){
        if(produtos[i].codigo == codigo){
            produtos[i].estoque = qtd;
            printf("Quantidade de estoque atualizada.\n");
            return;
        }
    }
    printf("Produto não encontrado.\n");
}

void exibirProduto(struct Produto *produtos, int cont){
    printf("\nPRODUTOS:\n");
    for(int i = 0; i < cont; i++){
        printf("Código: %d, descrição: %s\n", produtos[i].codigo, produtos[i].descricao);
    }if(cont == 0){
        printf("Nenhum produto encontrado.\n");
    }
}

void exibirProdutosSemEstoque(struct Produto *produtos, int cont){
    int estoqueZero = 0;
    printf("\nPRODUTOS SEM ESTOQUE\n");
    for(int i = 0; i < cont; i++){
        if(produtos[i].estoque == 0){
            printf("Código: %d, descrição: %s\n", produtos[i].codigo, produtos[i].descricao);
            estoqueZero++;
        }
    }if(estoqueZero == 0){
        printf("Não há produtos com estoque zero.\n");
    }
}
