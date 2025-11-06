#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------------------------------------------------------------------------------
// Estrutura da Mansão
struct Mansao {
    char Nome_Comodo[50];
    char Pista[100];              
    struct Mansao* esquerda; 
    struct Mansao* direita;
};

// Estrutura da Árvore de Pistas (BST)
struct PistaBST {
    char pista[100];
    struct PistaBST* esquerda;
    struct PistaBST* direita;
};

// Função para criar um cômodo
struct Mansao* criarComodo(char* nome, char* pista) {
    struct Mansao* novo = (struct Mansao*) malloc(sizeof(struct Mansao));
    strcpy(novo->Nome_Comodo, nome);
    strcpy(novo->Pista, pista);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Função para criar um novo nó de pista
struct PistaBST* criarPista(char* texto) {
    struct PistaBST* nova = (struct PistaBST*) malloc(sizeof(struct PistaBST));
    strcpy(nova->pista, texto);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Inserção na BST de pistas (ordem alfabética)
struct PistaBST* inserirPista(struct PistaBST* raiz, char* texto) {
    if (raiz == NULL)
        return criarPista(texto);

    if (strcmp(texto, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, texto);
    else if (strcmp(texto, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, texto);

    return raiz;
}

// Exibir pistas em ordem alfabética
void exibirPistas(struct PistaBST* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

// Exploração da mansão
void Explorar_Comodo(struct Mansao* raiz, char visitas[][50], int *totalVisitas, struct PistaBST** arvorePistas) {
    int escolha_jogador;
    struct Mansao* atual = raiz;

    // Pilha simples de ponteiros (para voltar)
    struct Mansao* caminho[100];
    int topo = 0;

    // Registra o primeiro cômodo visitado
    strcpy(visitas[(*totalVisitas)++], atual->Nome_Comodo);

    printf("\nVocê encontrou uma pista: %s\n", atual->Pista);
    *arvorePistas = inserirPista(*arvorePistas, atual->Pista); // insire a nova pista na árvore

    while (1) {
        printf("\nVocê está neste cômodo: %s\n", atual->Nome_Comodo);
        printf("Para onde quer ir?\n");
        printf("1 - Esquerda\n");
        printf("2 - Direita\n");
        printf("0 - Voltar\n");
        printf("Digite aqui: ");
        scanf("%d", &escolha_jogador);

        switch (escolha_jogador) {
        case 1: // Vai para a esquerda
            if (atual->esquerda != NULL) {
                caminho[topo++] = atual;  // empilha o cômodo atual
                atual = atual->esquerda;
                printf("Você foi para: %s\n", atual->Nome_Comodo);
                strcpy(visitas[(*totalVisitas)++], atual->Nome_Comodo); // registra visita
                printf("Você encontrou uma pista: %s\n", atual->Pista);
                *arvorePistas = inserirPista(*arvorePistas, atual->Pista); // insire a nova pista na árvore
            } else {
                printf("Não há cômodo à esquerda.\n");
            }
            break;

        case 2: // Vai para a direita
            if (atual->direita != NULL) {
                caminho[topo++] = atual;  // empilha o cômodo atual
                atual = atual->direita;
                printf("Você foi para: %s\n", atual->Nome_Comodo);
                strcpy(visitas[(*totalVisitas)++], atual->Nome_Comodo); // registra visita
                printf("Você encontrou uma pista: %s\n", atual->Pista);
                *arvorePistas = inserirPista(*arvorePistas, atual->Pista); // insire a nova pista na árvore
            } else {
                printf("Não há cômodo à direita.\n");
            }
            break;

        case 0: // Voltar
            if (topo == 0) {
                // Se está na raiz -> encerra
                printf("Você está no Hall de Entrada. Saindo da exploração...\n");
                return;
            } else {
                atual = caminho[--topo]; // desempilha o anterior
                printf("Você voltou para: %s\n", atual->Nome_Comodo);
            }
            break;

        default:
            printf("Opção inválida! Tente novamente.\n");
            break;
        }
    }
}

// Função para liberar a memória da árvore da mansão
void liberarMansao(struct Mansao* raiz) {
    if (raiz != NULL) {
        liberarMansao(raiz->esquerda);
        liberarMansao(raiz->direita);
        free(raiz);
    }
}

// Função para liberar a árvore de pistas
void liberarPistas(struct PistaBST* raiz) {
    if (raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}

// -----------------------------------------------------------------------------------------------------
// Função principal
int main() {
    // Definindo os comodos da Mansão com pistas
    struct Mansao* raiz = criarComodo("Hall de Entrada", "Um bilhete rasgado com a letra A.");
    raiz->esquerda = criarComodo("Sala de Estar", "Uma chave dourada caída no sofá.");
    raiz->direita = criarComodo("Biblioteca", "Um livro com páginas arrancadas.");
    raiz->esquerda->esquerda = criarComodo("Quarto", "Um colar antigo sobre a cama.");

    // Vetor para armazenar a sequência de salas visitadas
    char visitas[100][50];
    int totalVisitas = 0;

    // Árvore de pistas
    struct PistaBST* arvorePistas = NULL;

    // Exploração
    Explorar_Comodo(raiz, visitas, &totalVisitas, &arvorePistas);

    // Mostra a sequência de salas visitadas
    printf("\n--- Sequência de Cômodos Visitados ---\n");
    for (int i = 0; i < totalVisitas; i++) {
        printf("%d. %s\n", i + 1, visitas[i]);
    }

    // Exibe as pistas coletadas em ordem alfabética
    printf("\n--- Pistas Coletadas ---\n");
    exibirPistas(arvorePistas);

    // Libera memória
    liberarMansao(raiz);
    liberarPistas(arvorePistas);

    return 0;
}
