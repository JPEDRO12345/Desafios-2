#ifndef FILA_PILHA_H
#define FILA_PILHA_H

#define MAX 5  
#define MAXP 3 

// Struct das Peças
typedef struct {
    char nome[2];
    int id;
} Peca;

// Struct da Fila Circular
typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// Struct da Pilha
typedef struct {
    Peca itens[MAXP];
    int topo;
} Pilha;

// Funções da Fila
void inicializarFila(Fila *f);
void inserir_peca(Fila *f, Peca p);
void Jogar_peca(Fila *f, Peca *p);
void mostrar_pecas(Fila *f);

// Funções da Pilha
void inicializarPilha(Pilha *p);
int pilhaCheia(Pilha *p);
int pilhaVazia(Pilha *p);
void empilhar(Pilha *p, Peca nova);
Peca desempilhar(Pilha *p);
void mostrar_pilha(Pilha *p);

// Função de geração automática
Peca gerarPeca(int id);

#endif
