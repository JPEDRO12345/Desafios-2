#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 30
#define MAX_COR 10
#define TOTAL_MISSOES 5

// Struct do territorio
struct TERRITORIO {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int numero_tropas;
    char *missao; // armazenada dinamicamente com malloc
};

// Protótipos das funções
void Limpar_Buffer_Entrada();
void Mapa_Completo(int i, char *nome, char *cor, int tropas);
void Combate(int territorio_atacante, int territorio_defensor, char *nome_atacante, char *nome_defensor, int *tropa_atacante, int *tropa_defensora, char *cor_atacante, char *cor_defensor);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int contarTerritoriosPorCor(struct TERRITORIO* mapa, int tamanho, const char* cor, int apenasComTropas);
int verificarMissao(char* missao, struct TERRITORIO* mapa, int tamanho);

#endif