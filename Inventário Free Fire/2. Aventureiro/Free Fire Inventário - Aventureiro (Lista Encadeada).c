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
typedef struct No {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
    struct No *prox; // Ponteiro para o próximo nó
} No;

// Função responsavel pelo cadastro de itens
void Cadastro_Item(No **inicio) {
    char nomeTemp[MAX_NOME], tipoTemp[MAX_TIPO];
    int quantidade;

    printf("\n-----------Cadastro de Itens-----------\n");

    printf("Qual é o nome do item? ");
    fgets(nomeTemp, MAX_NOME, stdin);
    Remove_n(nomeTemp);

    // Verifica se já existe
    No *atual = *inicio;
    while(atual) {
        if(strcmp(atual->nome, nomeTemp) == 0) {
            printf("Erro: Um item com esse nome já existe!\n");
            return;
        }
        atual = atual->prox;
    }

    printf("Qual é o tipo do item? ");
    fgets(tipoTemp, MAX_TIPO, stdin);
    Remove_n(tipoTemp);

    printf("Qual é a quantidade do item? ");
    scanf("%d", &quantidade);
    Limpador_De_Buffer();

    // Cria novo nó
    No *novo = (No*)malloc(sizeof(No));
    strcpy(novo->nome, nomeTemp);
    strcpy(novo->tipo, tipoTemp);
    novo->quantidade = quantidade;
    novo->prox = NULL;

    // Insere no final
    if(*inicio == NULL) {
        *inicio = novo;
    } else {
        atual = *inicio;
        while(atual->prox) atual = atual->prox;
        atual->prox = novo;
    }

    printf("---------------------------------------\n\n");
}


// Função que apresenta os itens
void Apresentação_Itens(No *inicio){
    if(!inicio){
        printf("\nNenhum item cadastrado.\n");
        return;
    }

    printf("\n-----------Itens Cadastrados-----------\n");
    int i = 1;
    No *atual = inicio;
    while(atual){
        printf("Item %d: %s (%s) - %d\n", i++, atual->nome, atual->tipo, atual->quantidade);
        atual = atual->prox;
    }
    printf("\n---------------------------------------\n");
}

// Função responsável por remover um item da lista pelo nome
void Remover_Item(No **inicio){
    if(!*inicio){
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nomeBusca[MAX_NOME];
    printf("\nDigite o nome do item que deseja remover: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    Remove_n(nomeBusca);

    No *atual = *inicio;
    No *anterior = NULL;

    while(atual){
        if(strcmp(atual->nome, nomeBusca) == 0){
            if(anterior) anterior->prox = atual->prox;
            else *inicio = atual->prox; // removendo o primeiro nó
            free(atual);
            printf("Item removido com sucesso!\n");
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }

    printf("Item não encontrado!\n");
}

// Função que busca um item pelo nome (Busca Linear)
void Buscar_Item(No *inicio){
    if(!inicio){
        printf("\nNenhum item cadastrado.\n");
        return;
    }

    char nomeBusca[MAX_NOME];
    printf("\nDigite o nome exato do item que deseja localizar: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    Remove_n(nomeBusca);

    No *atual = inicio;
    int comparacoes = 0, i = 1;

    while(atual){
        comparacoes++;
        if(strcmp(atual->nome, nomeBusca) == 0){
            printf("\nItem encontrado:\n\n");
            printf("Item %d:\nNome: %s\nTipo: %s\nQuantidade %d\n\n", i, atual->nome, atual->tipo, atual->quantidade);
            printf("Número de comparações realizadas: %d\n", comparacoes);
            return;
        }
        atual = atual->prox;
        i++;
    }

    printf("\nItem '%s' não encontrado na mochila.\n", nomeBusca);
    printf("Número de comparações realizadas: %d\n", comparacoes);
}

// Função que deixa a lista em ordem alfabética pelo nome (Bubble Sort)
void Ordem_Alfabetica(No *inicio){
    if(!inicio){
        printf("\nNenhum item cadastrado para ordenar.\n");
        return;
    }

    int trocou;
    No *ptr;
    No *ultimo = NULL;

    do{
        trocou = 0;
        ptr = inicio;

        while(ptr->prox != ultimo){
            if(strcmp(ptr->nome, ptr->prox->nome) > 0){
                // troca os dados, não os nós
                No temp;
                strcpy(temp.nome, ptr->nome);
                strcpy(temp.tipo, ptr->tipo);
                temp.quantidade = ptr->quantidade;

                strcpy(ptr->nome, ptr->prox->nome);
                strcpy(ptr->tipo, ptr->prox->tipo);
                ptr->quantidade = ptr->prox->quantidade;

                strcpy(ptr->prox->nome, temp.nome);
                strcpy(ptr->prox->tipo, temp.tipo);
                ptr->prox->quantidade = temp.quantidade;

                trocou = 1;
            }
            ptr = ptr->prox;
        }
        ultimo = ptr;
    }while(trocou);

    printf("\nItens ordenados em ordem alfabética!\n");
}

//----------------------------------------------------------------------------------------------------------------------

// Função Principal
int main(){
    No *mochila = NULL; // Ponteiro para o início da lista encadeada
    int opcao;

    do
    {
        printf("\n-----------Inventário-----------\n");
        printf("O que deseja fazer?\n");
        printf("1-Inserir item\n2-Remover Item da Lista\n3-Localizar um item na lista\n4-Listar itens na mochila\n5-Deixar em ordem Alfabética\n0-Sair\n");
        printf("Digite aqui: ");
        scanf("%d", &opcao);
        Limpador_De_Buffer();

        switch (opcao)
        {
        case 1:
            Cadastro_Item(&mochila);
            break;
        
        case 2:
            Remover_Item(&mochila); 
            break;
        case 3:
            Buscar_Item(mochila);
            break;
        
        case 4:
            Apresentação_Itens(mochila);
            break;

        case 5:
            Ordem_Alfabetica(mochila);
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
        Apresentação_Itens(mochila);
    }
    } while (opcao != 0);

    // Liberação de memória da lista 
    No *atual = mochila;
    while(atual) {
        No *prox = atual->prox;
        free(atual);
        atual = prox;
    }
}
