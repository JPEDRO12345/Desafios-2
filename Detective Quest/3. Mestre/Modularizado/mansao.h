#ifndef MANSAO_H
#define MANSAO_H

#include "pistas.h"

struct Mansao {
    char Nome_Comodo[50];
    char Pista[100];
    struct Mansao* esquerda;
    struct Mansao* direita;
};

struct Mansao* criarComodo(char* nome, char* pista);
void Explorar_Comodo(struct Mansao* raiz, char visitas[][50], int *totalVisitas, struct PistaBST** arvorePistas);
void liberarMansao(struct Mansao* raiz);

#endif
