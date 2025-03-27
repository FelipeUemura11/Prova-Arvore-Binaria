#include<stdio.h>
#include<stdlib.h>

struct Pagamento {
    int id;
    float valor;
    char dataVencimento[8];
    char status[9];
};
struct No {
    struct Pagamento pagamento;
    struct No *esq;
    struct No *dir;
};

void liberarMemoriaArvore(struct No *raiz) {
    if (raiz != NULL) {
        liberarMemoriaArvore(raiz->esq);
        liberarMemoriaArvore(raiz->dir);
        free(raiz);
    }
}

void inserirFatura(struct No **raiz, struct Pagamento novoPagamento){

    if (*raiz == NULL) {
        *raiz = (struct No *)malloc(sizeof(struct No));
        if (*raiz != NULL) {
            (*raiz)->pagamento = novoPagamento;
            (*raiz)->esq = NULL;
            (*raiz)->dir = NULL;
        } else {
            printf("ERROR : Insercao invalida!\n");
        }
    } else {
        if (novoPagamento.id < (*raiz)->pagamento.id) {
            inserirProduto(&(*raiz)->esq, novoPagamento);
        } else if (novoPagamento.id > (*raiz)->pagamento.id) {
            inserirProduto(&(*raiz)->dir, novoPagamento);
        } else {
            printf("Produto duplicado.\n");
        }
    }

}

int main(void){

    struct No *raiz = NULL;
    struct Pagamento pagamento;
    int opcao = -1;

    while (opcao != 0) {
        printf("\n == Pagamento == \n");
        printf(" [1] Inserir fatura nova  \n");
        printf(" [2] Busca de faturas \n");
        printf(" [3] Alterar fatura \n");
        printf(" [4] Remover uma fatura \n");
        printf(" [5] Exibir todas as informacoes \n");
        printf(" [0] Sair \n");

        printf("Informe uma opcao: ");
        scanf("%i", &opcao);

        switch(opcao){
            case 1:
                printf("Informe o id da fatura: ");
                getchar();
                scanf("%i", &pagamento.id);

                printf("Informe o nome do pagamento: ");
                getchar();
                fgets(pagamento.dataVencimento, sizeof(pagamento.dataVencimento), stdin);
                pagamento.dataVencimento[strcspn(pagamento.dataVencimento, "\n")] = '\0';

                printf("Informe o valor do pagamento: ");
                scanf("%f", &pagamento.valor);

                pagamento.status[9] = "pendente";

                inserirFatura(&raiz, pagamento);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 0:
                liberarMemoriaArvore(raiz);
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    }
}