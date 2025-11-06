#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila_pilha.h"

// Inicialização da Fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Inicialização da Pilha
void inicializarPilha(Pilha *p) {
    p->topo = 0;
}

// Verificações da Pilha
int pilhaCheia(Pilha *p) {
    return p->topo == MAXP;
}

int pilhaVazia(Pilha *p) {
    return p->topo == 0;
}

// Empilhar
void empilhar(Pilha *p, Peca nova) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia. Não é possível reservar mais peças.\n");
        return;
    }
    p->itens[p->topo++] = nova;
}

// Desempilhar
Peca desempilhar(Pilha *p) {
    Peca removida = {"-", -1};
    if (pilhaVazia(p)) {
        printf("Pilha vazia. Nenhuma peça reservada.\n");
        return removida;
    }
    p->topo--;
    return p->itens[p->topo];
}

// Inserir na fila
void inserir_peca(Fila *f, Peca p) {
    if (f->total == MAX) {
        printf("Fila cheia. Não é possível inserir.\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

// Remover da fila
void Jogar_peca(Fila *f, Peca *p) {
    if (f->total == 0) {
        printf("Fila vazia. Não é possível jogar.\n");
        return;
    }
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

// Gerar peça aleatória
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[4][2] = {"I", "O", "T", "L"};
    int tipoAleatorio = rand() % 4;
    strcpy(nova.nome, tipos[tipoAleatorio]);
    nova.id = id;
    return nova;
}

// Mostrar fila
void mostrar_pecas(Fila *f) {
    printf("Fila de Peças: ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX)
        printf("[%s, %d] ", f->itens[idx].nome, f->itens[idx].id);
    printf("\n");
}

// Mostrar pilha
void mostrar_pilha(Pilha *p) {
    printf("Pilha de Reserva (Topo -> Base): ");
    if (p->topo == 0)
        printf("(vazia)");
    else
        for (int i = p->topo - 1; i >= 0; i--)
            printf("[%s, %d] ", p->itens[i].nome, p->itens[i].id);
    printf("\n");
}