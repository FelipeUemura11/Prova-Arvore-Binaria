#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
            inserirFatura(&(*raiz)->esq, novoPagamento);
        } else if (novoPagamento.id > (*raiz)->pagamento.id) {
            inserirFatura(&(*raiz)->dir, novoPagamento);
        } else {
            printf("Id ja existe.\n");
        }
    }

}

struct No *buscarFatura(struct No *raiz, int buscarId) {
    if (raiz == NULL || raiz->pagamento.id == buscarId) {
        return raiz;
    }
    if (buscarId < raiz->pagamento.id) {
        return buscarFatura(raiz->esq, buscarId);
    }
    return buscarFatura(raiz->dir, buscarId);
}

void alterarFatura(struct No **raiz, int faturaId){

    int novaQuant = 0;
    char novoStatus[9] = "pago";

    struct No *encontrado = buscarFatura(*raiz, faturaId);
    if(encontrado != NULL){

        strcpy(encontrado->pagamento.status, novoStatus);

        printf("\n=============\n");
        printf("Pagamento Atualizado!\n");
        printf("Id: %i\n", encontrado->pagamento.id);
        printf("Data de vencimento: %s\n", encontrado->pagamento.dataVencimento);
        printf("Valor: %.2f\n", encontrado->pagamento.valor);
        printf("Status: %s\n", encontrado->pagamento.status);
        printf("=============\n");
    }else{
        printf("Produto nao encontrado...\n");
    }

}

void exibirFaturas(struct No *raiz){
    if(raiz != NULL){
        exibirFaturas(raiz->esq);
        printf("\n---------------------------------\n");
        printf("Numero da fatura(ID): %i\n", raiz->pagamento.id);
        printf("Data de Vencimento: %s\n", raiz->pagamento.dataVencimento);
        printf("Valor: %f\n", raiz->pagamento.valor);
        printf("Status: %s\n", raiz->pagamento.status);
        exibirFaturas(raiz->dir);
    }
}

int removerFatura(struct No **raiz, int removerId) {
    if (*raiz == NULL) {
        printf("Nao ha noh [%i] na arvore!\n", removerId);
        return -1;
    }
    if (removerId < (*raiz)->pagamento.id) {
        return removerFatura(&((*raiz)->esq), removerId);
    } else if (removerId > (*raiz)->pagamento.id) {
        return removerFatura(&((*raiz)->dir), removerId);
    } else {
        struct No *temp = *raiz;
        if (temp->esq == NULL) {
            *raiz = temp->dir;
            free(temp);
        } else if (temp->dir == NULL) {
            *raiz = temp->esq;
            free(temp);
        } else {
            struct No *aux = temp->dir;
            struct No *paiAux = temp;
            while (aux->esq != NULL) {
                paiAux = aux;
                aux = aux->esq;
            }
            temp->pagamento = aux->pagamento;
            if (paiAux->esq == aux) {
                paiAux->esq = aux->dir;
            } else {
                paiAux->dir = aux->dir;
            }
            free(aux);
        }
        printf("Pagamento de id [%i] removido!\n", removerId);
        return 0;
    }
}

int main(void){

    struct No *raiz = NULL;
    struct Pagamento pagamento;
    int opcao = -1, idBuscar, idAlterar, idRemover;
    char pendente[9] = "pendente";

    while (opcao != 0) {
        printf("\n == Pagamento == \n");
        printf(" [1] Inserir fatura nova  \n");
        printf(" [2] Busca de faturas \n");
        printf(" [3] Alterar fatura \n");
        printf(" [4] Remover uma fatura \n");
        printf(" [5] Exibir todas as informacoes \n");
        printf(" [0] Sair \n");

        printf(" >> Informe uma opcao: ");
        scanf("%i", &opcao);

        switch(opcao){
            case 1:
                printf("Informe o id da fatura: ");
                scanf("%i", &pagamento.id);
                getchar();

                printf("Informe a data de vencimento: ");
                getchar();
                fgets(pagamento.dataVencimento, sizeof(pagamento.dataVencimento), stdin);
                pagamento.dataVencimento[strcspn(pagamento.dataVencimento, "\n")] = '\0';

                printf("Informe o valor do pagamento: ");
                scanf("%f", &pagamento.valor);
                getchar();

                strcpy(pagamento.status, pendente);

                inserirFatura(&raiz, pagamento);
                break;
            case 2:
                printf("Informe o id da fatura que deseja BUSCAR: ");
                scanf("%i", &idBuscar);
                struct No *buscado = buscarFatura(raiz, idBuscar);
                if (buscado != NULL) {
                    printf("\nFatura encontrada!\n");
                    printf("Id: %i\n", buscado->pagamento.id);
                    printf("Data de Vencimento: %s\n", buscado->pagamento.dataVencimento);
                    printf("Valor: %.2f\n", buscado->pagamento.valor);
                    printf("Status: %s\n", buscado->pagamento.status);
                } else {
                    printf("Pagamento nao encontrado...\n");
                }
                break;
            case 3:
                printf("Digite o id do pagamento que deseje ALTERAR: ");
                scanf("%i", &idAlterar);
                alterarFatura(&raiz, idAlterar);
                break;
            case 4:
                printf("Informe o id do pagamento que deseja REMOVER: ");
                scanf("%i", &idRemover);
                removerFatura(&raiz, idRemover);
                break;
            case 5:
                printf("\nExibir Faturas: \n");
                exibirFaturas(raiz);
                break;
            case 0:
                liberarMemoriaArvore(raiz);
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    }
}