#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mansao.h"
#include "pistas.h"
#include "hash.h"

// Função para criar um cômodo
struct Mansao* criarComodo(char* nome, char* pista) {
    struct Mansao* novo = (struct Mansao*) malloc(sizeof(struct Mansao));
    strcpy(novo->Nome_Comodo, nome);
    strcpy(novo->Pista, pista);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Exploração da mansão
void Explorar_Comodo(struct Mansao* raiz, char visitas[][50], int *totalVisitas, struct PistaBST** arvorePistas) {
    int escolha_jogador;
    struct Mansao* atual = raiz;

    // Pilha simples de ponteiros (para voltar)
    struct Mansao* caminho[100];
    int topo = 0;

    // Registra o primeiro cômodo visitado
    strcpy(visitas[(*totalVisitas)++], atual->Nome_Comodo);

    printf("\nVocê encontrou uma pista: %s\n", atual->Pista);
    *arvorePistas = inserirPista(*arvorePistas, atual->Pista); // insire a nova pista na árvore

    while (1) {
        printf("\nVocê está neste cômodo: %s\n", atual->Nome_Comodo);
        printf("Para onde quer ir?\n");
        printf("1 - Esquerda\n");
        printf("2 - Direita\n");
        printf("0 - Voltar\n");
        printf("Digite aqui: ");
        if (scanf("%d", &escolha_jogador) != 1) {
            // entrada inválida: limpa stdin e continua
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Entrada inválida. Tente novamente.\n");
            continue;
        }

        switch (escolha_jogador) {
        case 1: // Vai para a esquerda
            if (atual->esquerda != NULL) {
                caminho[topo++] = atual;  // empilha o cômodo atual
                atual = atual->esquerda;
                printf("Você foi para: %s\n", atual->Nome_Comodo);
                strcpy(visitas[(*totalVisitas)++], atual->Nome_Comodo); // registra visita
                printf("Você encontrou uma pista: %s\n", atual->Pista);
                *arvorePistas = inserirPista(*arvorePistas, atual->Pista); // insere a nova pista na árvore
            } else {
                printf("Não há cômodo à esquerda.\n");
            }
            break;

        case 2: // Vai para a direita
            if (atual->direita != NULL) {
                caminho[topo++] = atual;  // empilha o cômodo atual
                atual = atual->direita;
                printf("Você foi para: %s\n", atual->Nome_Comodo);
                strcpy(visitas[(*totalVisitas)++], atual->Nome_Comodo); // registra visita
                printf("Você encontrou uma pista: %s\n", atual->Pista);
                *arvorePistas = inserirPista(*arvorePistas, atual->Pista); // insere a nova pista na árvore
            } else {
                printf("Não há cômodo à direita.\n");
            }
            break;

        case 0: // Voltar
            if (topo == 0) {
                // Se está na raiz -> encerra
                printf("Você está no Hall de Entrada. Encerrando exploração...\n");
                return;
            } else {
                atual = caminho[--topo]; // desempilha o anterior
                printf("Você voltou para: %s\n", atual->Nome_Comodo);
            }
            break;

        default:
            printf("Opção inválida! Tente novamente.\n");
            break;
        }
    }
}

// Função para liberar a memória da árvore da mansão
void liberarMansao(struct Mansao* raiz) {
    if (raiz != NULL) {
        liberarMansao(raiz->esquerda);
        liberarMansao(raiz->direita);
        free(raiz);
    }
}
