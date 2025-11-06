#ifndef INVENTARIO_H
#define INVENTARIO_H

#define MAX_NOME 30
#define MAX_TIPO 20
#define MAX_LISTA 20

// Struct com as caracterisitcas dos itens
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
    int prioridade;
} item;

// Funções principais
void Cadastro_Item(item lista[], int *contador);
void Apresentacao_Itens(item lista[], int contador);
void Remover_Item(item lista[], int *contador);

// Funções de ordenação
void Ordem_Alfabetica(item lista[], int contador);
void Ordenar_Tipo(item lista[], int contador);
void Ordenar_Prioridade(item lista[], int contador);

// Busca
void Buscar_Item_Binario(item lista[], int contador);

// Utilitários
void Limpador_De_Buffer();
void Remove_n(char *str);

#endif
