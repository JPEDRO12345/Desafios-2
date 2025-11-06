#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pistas.h"
#include "hash.h"

// Função para criar um novo nó de pista
struct PistaBST* criarPista(char* texto) {
    struct PistaBST* nova = (struct PistaBST*) malloc(sizeof(struct PistaBST));
    strcpy(nova->pista, texto);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Inserção na BST de pistas (ordem alfabética)
struct PistaBST* inserirPista(struct PistaBST* raiz, char* texto) {
    if (raiz == NULL)
        return criarPista(texto);

    int cmp = strcmp(texto, raiz->pista);
    if (cmp < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, texto);
    else if (cmp > 0)
        raiz->direita = inserirPista(raiz->direita, texto);
    // se igual, não insere duplicata (mantemos única)
    return raiz;
}

// Exibir pistas em ordem alfabética
void exibirPistas(struct PistaBST* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

// Função auxiliar: percorre BST e conta quantas pistas apontam para 'suspeito'
// usa Buscar_Pista_Sus para encontrar quem está associado a cada pista
int contarPistasDoSuspeito_helper(struct PistaBST* raiz, const char* suspeito) {
    if (raiz == NULL) return 0;
    int count = 0;
    // percorre esquerda
    count += contarPistasDoSuspeito_helper(raiz->esquerda, suspeito);
    // verifica esta pista
    const char* s = Buscar_Pista_Sus(raiz->pista);
    if (s != NULL && strcmp(s, suspeito) == 0) count++;
    // percorre direita
    count += contarPistasDoSuspeito_helper(raiz->direita, suspeito);
    return count;
}

int contarPistasDoSuspeito(struct PistaBST* raiz, const char* suspeito) {
    return contarPistasDoSuspeito_helper(raiz, suspeito);
}

// Função para liberar a árvore de pistas
void liberarPistas(struct PistaBST* raiz) {
    if (raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}
