#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 30
#define MAX_TIPO 20
#define MAX_LISTA 10

//----------------------------------------------------------------------------------------------------------------------

// Função que Limpa o buffer para evitar problemas ao usar fgets
void Limpador_De_Buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa 
}

// Para Remover o '\n' automatico do fgets
void Remove_n(char *str){
    str[strcspn(str, "\n")] = '\0'; // Remove o '\n' se houver
}

// Struct com as caracterisitcas dos itens
typedef struct
{
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} item;

// Função responsavel pelo cadastro de itens
void Cadastro_Item(item lista[], int *contador){
    // Verifica se a mochila está cheia
    if(*contador >= MAX_LISTA){
        printf("\nA mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    char nomeTemp[MAX_NOME];

    printf("\n-----------Cadastro de Itens-----------\n");
    printf("Item %d\n", *contador + 1);

    printf("Qual é o nome do item? ");
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

    printf("Qual é o tipo do item? ");
    fgets(lista[*contador].tipo, MAX_TIPO, stdin);
    Remove_n(lista[*contador].tipo);

    printf("Qual é a quantidade do item? ");
    scanf("%d", &lista[*contador].quantidade);
    Limpador_De_Buffer();

    (*contador)++; // Incrementa o contador de itens cadastrados
    printf("---------------------------------------\n\n");
}

// Função que apresenta os itens
void Apresentação_Itens(item lista[], int contador){
    if(contador == 0){
        printf("\nNenhum item cadastrado.\n");
        return;
    }
    printf("\n-----------Itens Cadastrados-----------\n");
    for (int i = 0; i < contador; i++)
    {
        printf("Item %d: %s (%s) - %d\n", i+1, lista[i].nome, lista[i].tipo, lista[i].quantidade);
    }
    printf("\n---------------------------------------\n");
}

// Função responsável por remover um item da lista pelo nome
void Remover_Item(item lista[], int *contador) {
    // Verifica se a mochila tem algum item
    if (*contador == 0) {
        printf("\nA mochila está vazia! Nenhum item para remover.\n");
        return;
    }

    char nomeBusca[MAX_NOME]; // string temporária para armazenar o nome do item que o usuário vai digitar
    printf("\nDigite o nome do item que deseja remover: ");
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
        printf("Item não encontrado!\n");
        return;
    }

    // Desloca os itens posteriores para preencher o espaço
    for (int i = indice; i < *contador - 1; i++) {
        lista[i] = lista[i + 1];
    }

    (*contador)--; // Decrementa o contador
}

// Função que busca um item pelo nome (Busca Linear)
void Buscar_Item(item lista[], int contador) {
    // Verifica se há itens cadastrados
    if (contador == 0) {
        printf("\nNenhum item cadastrado.\n");
        return;
    }

    char nomeBusca[MAX_NOME];
    printf("\nDigite o nome exato do item que deseja localizar: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    Remove_n(nomeBusca); 

    int comparacoes = 0;
    // Busca linear
    for (int i = 0; i < contador; i++) {
        comparacoes++; // Conta a comparação
        // Compara a string digitada com as strings de nome dos itens cadastrados
        if (strcmp(lista[i].nome, nomeBusca) == 0) { 
            printf("\nItem encontrado:\n\n");
            printf("Item %d:\nNome: %s\nTipo: %s\nQuantidade %d\n\n", i + 1, lista[i].nome, lista[i].tipo, lista[i].quantidade);
            printf("Número de comparações realizadas: %d\n", comparacoes);
            return; // Sai da função após encontrar o item
        }
    }

    printf("\nItem '%s' não encontrado na mochila.\n", nomeBusca);
    printf("Número de comparações realizadas: %d\n", comparacoes);
}

// Função que deixa a lista em ordem alfabética pelo nome (Bubble Sort)
void Ordem_Alfabetica(item lista[], int contador){
    // Verifica se há itens para ordenar
    if(contador == 0){ 
        printf("\nNenhum item cadastrado para ordenar.\n");
        return;
    }

    for(int i = 0; i < contador - 1; i++){
        for(int j = 0; j < contador - i - 1; j++){
            // Compara duas strings
            if(strcmp(lista[j].nome, lista[j+1].nome) > 0){
                // Troca os itens de posição
                item temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
    printf("\nItens ordenados em ordem alfabética!\n");
}

// Função que realiza a Busca Binária
void Buscar_Item_Binario(item lista[], int contador) {
    // Verifica se há itens cadastrados
    if (contador == 0) {
        printf("\nNenhum item cadastrado.\n");
        return;
    }

    // Ordena a lista antes de buscar
    Ordem_Alfabetica(lista, contador);

    char nomeBusca[MAX_NOME];
    printf("\nDigite o nome exato do item que deseja localizar (Busca Binária): ");
    fgets(nomeBusca, MAX_NOME, stdin);
    Remove_n(nomeBusca);

    int inicio = 0;
    int fim = contador - 1;
    int encontrado = 0;
    int comparacoes = 0; 

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++; // Conta a comparação
        int cmp = strcmp(nomeBusca, lista[meio].nome);

        if (cmp == 0) {
            // Item encontrado
            printf("\nItem encontrado:\n\n");
            printf("Item %d:\nNome: %s\nTipo: %s\nQuantidade %d\n\n", meio + 1, lista[meio].nome, lista[meio].tipo, lista[meio].quantidade);
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

    if (!encontrado) {
        printf("\nItem '%s' não encontrado na mochila.\n", nomeBusca);
    }
    printf("Número de comparações realizadas: %d\n", comparacoes);
}

//----------------------------------------------------------------------------------------------------------------------

// Função Principal
int main(){
    item mochila[MAX_LISTA]; // Array que armazena as informações dos itens
    int opcao;
    int contador = 0; // Contador para gerenciar a adicição de itens

    do
    {
        printf("\n-----------Inventário-----------\n");
        printf("O que deseja fazer?\n");
        printf("1-Inserir item\n2-Remover Item da Lista\n3-Localizar um item na lista\n4-Listar itens na mochila\n5-Deixar em ordem Alfabética\n6-Busca Binária (faz ordenação automaticamente)\n0-Sair\n");
        printf("Digite aqui: ");
        scanf("%d", &opcao);
        Limpador_De_Buffer();

        switch (opcao)
        {
        case 1:
            Cadastro_Item(mochila, &contador); // Função responsavel pelo Cadastro de itens
            break;
        
        case 2:
            Remover_Item(mochila, &contador);
            break;
        case 3:
            Buscar_Item(mochila, contador);
            break;
        
        case 4:
            Apresentação_Itens(mochila, contador);
            break;

        case 5:
            Ordem_Alfabetica(mochila, contador);
            break;

        case 6:
            Buscar_Item_Binario(mochila, contador);
            break;
        
        case 0:
        printf("\nSaindo do programa: Pressione Enter\n");
        break;
        break;
        
        default:
            printf("\nErro! Digite um valor válido\n");
            break;
        }
    if (opcao !=0 && opcao != 4) // Só executa se o valor escolhido for diferente de 0 e de 4
    {
        // Chamada da função responsável pela apresentação dos itens cadastrados
        Apresentação_Itens(mochila, contador);
    }
    } while (opcao != 0);
}