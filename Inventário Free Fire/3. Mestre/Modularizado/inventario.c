#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "inventario.h"

#define MAX_NOME 30
#define MAX_TIPO 20
#define MAX_LISTA 20

// Função responsavel pelo cadastro de itens
void Cadastro_Item(item lista[], int *contador){
    // Verifica se a mochila está cheia
    if(*contador >= MAX_LISTA){
        printf("\nA mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    char nomeTemp[MAX_NOME];

    printf("\n-----------Cadastro de Componentes-----------\n");
    printf("Item %d\n", *contador + 1);

    printf("Qual é o nome do Componente? ");
    fgets(nomeTemp, MAX_NOME, stdin);
    Remove_n(nomeTemp);

    // Verifica se o nome já existe na lista
    for (int i = 0; i < *contador; i++) {
        if (strcmp(lista[i].nome, nomeTemp) == 0) {
            printf("Erro: Um item com esse nome já existe!\nPressione enter duas vezes\n");
            Limpador_De_Buffer(); 
            getchar(); // Espera o usuário apertar Enter
            return; // Sai da função sem adicionar
        }
    }

    // Se o nome não existe, adiciona o item
    strcpy(lista[*contador].nome, nomeTemp);

    printf("Qual é o tipo do Componente (Estrutural, Eletronico, Energia)? ");
    fgets(lista[*contador].tipo, MAX_TIPO, stdin);
    Remove_n(lista[*contador].tipo);

    printf("Qual é a quantidade do item? ");
    scanf("%d", &lista[*contador].quantidade);
    Limpador_De_Buffer();

    printf("Qual é a prioridade de Montagem (1-5)?");
    scanf("%d", &lista[*contador].prioridade);
    Limpador_De_Buffer();

    (*contador)++; // Incrementa o contador de itens cadastrados
    printf("---------------------------------------\n\n");
}

// Função que apresenta os itens
void Apresentacao_Itens(item lista[], int contador){
    if(contador == 0){
        printf("\nNenhum Componente cadastrado.\n");
        return;
    }
    printf("\n-----------Componentes cadastrados-----------\n");
    for (int i = 0; i < contador; i++)
    {
        printf("Componente %d: %s (%s) - %d | Prioridade: %d\n", i+1, lista[i].nome, lista[i].tipo, lista[i].quantidade, lista[i].prioridade);
    }
    printf("\n---------------------------------------\n");
}

// Função responsável por remover um item da lista pelo nome
void Remover_Item(item lista[], int *contador) {
    // Verifica se a mochila tem algum item
    if (*contador == 0) {
        printf("\nA mochila está vazia! Nenhum Componente para remover.\n");
        return;
    }

    char nomeBusca[MAX_NOME]; // string temporária para armazenar o nome do item que o usuário vai digitar
    printf("\nDigite o nome do Componente que deseja remover: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    Remove_n(nomeBusca);

    // Busca linear pelo nome
    int indice = -1;
    for (int i = 0; i < *contador; i++) { // Verifica se na lista há algum nome que corresponda ao digitado
        if (strcmp(lista[i].nome, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Componente não encontrado!\n");
        return;
    }

    // Desloca os itens posteriores para preencher o espaço
    for (int i = indice; i < *contador - 1; i++) {
        lista[i] = lista[i + 1];
    }

    (*contador)--; // Decrementa o contador
}

// Função que deixa a lista em ordem alfabética pelo nome (Bubble Sort)
void Ordem_Alfabetica(item lista[], int contador){
    // Verifica se há itens para ordenar
    if(contador == 0){ 
        printf("\nNenhum Componente cadastrado para ordenar.\n");
        return;
    }

    clock_t inicio, fim; // variáveis para medir o tempo
    double tempo_execucao; // tempo em segundos
    inicio = clock(); // marca o início
    int comparacoes = 0;
    for(int i = 0; i < contador - 1; i++){
        for(int j = 0; j < contador - i - 1; j++){
            // Compara duas strings
            comparacoes++;
            if(strcmp(lista[j].nome, lista[j+1].nome) > 0){
                // Troca os itens de posição
                item temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
    fim = clock(); // marca o final
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nComponentes ordenados em ordem alfabética!\n");
    printf("Número de comparações realizadas: %d\n", comparacoes);
    printf("Tempo de execução: %.6f segundos\n", tempo_execucao);
}

// Função que ordena os componentes por Tipo
void Ordenar_Tipo(item lista[], int contador){
    // Verifica se há itens para ordenar
    if(contador == 0){ 
        printf("\nNenhum Componente cadastrado para ordenar.\n");
        return;
    }

    clock_t inicio, fim; // variáveis para medir o tempo
    double tempo_execucao; // tempo em segundos
    inicio = clock(); // marca o início
    int comparacoes = 0;
    for(int i = 0; i < contador - 1; i++){
        for(int j = 0; j < contador - i - 1; j++){
            comparacoes++;
            // Compara duas strings
            if(strcmp(lista[j].tipo, lista[j+1].tipo) > 0){
                // Troca os itens de posição
                item temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
    fim = clock(); // marca o final
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nComponentes ordenados por tipo!\n");
    printf("Número de comparações realizadas: %d\n", comparacoes);
    printf("Tempo de execução: %.6f segundos\n", tempo_execucao);
}

// Função que ordena os componentes por Prioridade
void Ordenar_Prioridade(item lista[], int contador){
    // Verifica se há itens para ordenar
    if(contador == 0){ 
        printf("\nNenhum Componente cadastrado para ordenar.\n");
        return;
    }
    clock_t inicio, fim; // variáveis para medir o tempo
    double tempo_execucao; // tempo em segundos
    inicio = clock(); // marca o início
    int comparacoes = 0;
    for(int i = 0; i < contador - 1; i++){
        // Compara dois valores
        for(int j = 0; j < contador - i - 1; j++){
            comparacoes++;
            if(lista[j].prioridade < lista[j+1].prioridade){
                // Troca os itens de posição
                item temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
    fim = clock(); // marca o final
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nComponentes ordenados por Prioridade.\n");
    printf("Número de comparações realizadas: %d\n", comparacoes);
    printf("Tempo de execução: %.6f segundos\n", tempo_execucao);
}

// Função que realiza a Busca Binária
void Buscar_Item_Binario(item lista[], int contador) {
    // Verifica se há itens cadastrados
    if (contador == 0) {
        printf("\nNenhum Componente cadastrado.\n");
        return;
    }

    // Ordena a lista antes de buscar
    Ordem_Alfabetica(lista, contador);

    char nomeBusca[MAX_NOME];
    printf("\nDigite o Componente exato do item que deseja localizar (Busca Binária): ");
    fgets(nomeBusca, MAX_NOME, stdin);
    Remove_n(nomeBusca);

    int inicio = 0;
    int fim = contador - 1;
    int encontrado = 0;
    int comparacoes = 0; 

    clock_t inicioC, fimC; // variáveis para medir o tempo
    double tempo_execucao; // tempo em segundos
    inicioC = clock(); // marca o início

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++; // Conta a comparação
        int cmp = strcmp(nomeBusca, lista[meio].nome);

        if (cmp == 0) {
            // Item encontrado
            printf("\nComponente encontrado:\n\n");
            printf("Componente %d:\nNome: %s\nTipo: %s\nQuantidade %d\nPrioridade: %d\n\n", meio + 1, lista[meio].nome, lista[meio].tipo, lista[meio].quantidade, lista[meio].prioridade);
            encontrado = 1;
            break;
        } else if (cmp < 0) {
            // Procurar na metade esquerda
            fim = meio - 1;
        } else {
            // Procurar na metade direita
            inicio = meio + 1;
        }
    }
    fimC = clock(); // marca o final
    tempo_execucao = (double)(fimC - inicioC) / CLOCKS_PER_SEC;

    if (!encontrado) {
        printf("\nComponente '%s' não encontrado na mochila.\n", nomeBusca);
    }

    printf("Número de comparações realizadas: %d\n", comparacoes);
    printf("Tempo de execução: %.6f segundos\n", tempo_execucao);
}
