#ifndef PISTAS_H
#define PISTAS_H

struct PistaBST {
    char pista[100];
    struct PistaBST* esquerda;
    struct PistaBST* direita;
};

struct PistaBST* criarPista(char* texto);
struct PistaBST* inserirPista(struct PistaBST* raiz, char* texto);
void exibirPistas(struct PistaBST* raiz);
int contarPistasDoSuspeito(struct PistaBST* raiz, const char* suspeito);
void liberarPistas(struct PistaBST* raiz);

#endif
