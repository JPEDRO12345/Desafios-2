#ifndef HASH_H
#define HASH_H

#define TAM_TAB_HASH 101

typedef struct AssociacaoPistaSuspeito {
    char chave[100];         
    char suspeito[50];       
    struct AssociacaoPistaSuspeito* prox;
} AssociacaoPistaSuspeito;

extern AssociacaoPistaSuspeito* tabelaHash[TAM_TAB_HASH];

unsigned long gerarHash(const char* str);
void Inserir_Hash(const char* chave, const char* suspeito);
const char* Buscar_Pista_Sus(const char* chave);
void liberarHash();

#endif