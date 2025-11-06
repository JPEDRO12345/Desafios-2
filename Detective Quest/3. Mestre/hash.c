#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

// Tabela hash global
AssociacaoPistaSuspeito* tabelaHash[TAM_TAB_HASH];

// Gera um hash a partir de uma string fornecida, que será usado como índice na tabela hash
unsigned long gerarHash(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

// Insere uma associação pista | suspeito na tabela hash
void Inserir_Hash(const char* chave, const char* suspeito) {
    unsigned long h = gerarHash(chave) % TAM_TAB_HASH;
    // Verifica se já existe
    AssociacaoPistaSuspeito* cur = tabelaHash[h];
    while (cur) {
        if (strcmp(cur->chave, chave) == 0) {
            // atualiza suspeito se necessário
            strncpy(cur->suspeito, suspeito, sizeof(cur->suspeito)-1);
            cur->suspeito[sizeof(cur->suspeito)-1] = '\0';
            return;
        }
        cur = cur->prox;
    }
    // Cria novo nó
    AssociacaoPistaSuspeito* novo = (AssociacaoPistaSuspeito*) malloc(sizeof(AssociacaoPistaSuspeito));
    strncpy(novo->chave, chave, sizeof(novo->chave)-1);
    novo->chave[sizeof(novo->chave)-1] = '\0';
    strncpy(novo->suspeito, suspeito, sizeof(novo->suspeito)-1);
    novo->suspeito[sizeof(novo->suspeito)-1] = '\0';
    novo->prox = tabelaHash[h];
    tabelaHash[h] = novo;
}

// Retorna ponteiro para suspeito (string) associado à chave, ou NULL se não existir
const char* Buscar_Pista_Sus(const char* chave) {
    unsigned long h = gerarHash(chave) % TAM_TAB_HASH;
    AssociacaoPistaSuspeito* cur = tabelaHash[h];
    while (cur) {
        if (strcmp(cur->chave, chave) == 0) return cur->suspeito;
        cur = cur->prox;
    }
    return NULL;
}

// Libera tabela hash
void liberarHash() {
    for (int i = 0; i < TAM_TAB_HASH; ++i) {
        AssociacaoPistaSuspeito* cur = tabelaHash[i];
        while (cur) {
            AssociacaoPistaSuspeito* prox = cur->prox;
            free(cur);
            cur = prox;
        }
        tabelaHash[i] = NULL;
    }
}