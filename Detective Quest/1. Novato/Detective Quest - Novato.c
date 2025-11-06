#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// Estrutura da mansão
struct Mansao {
    char Nome_Comodo[50];
    struct Mansao* esquerda; 
    struct Mansao* direita;
};

// Função para criar um cômodo
struct Mansao* criarComodo(char* valor) {
    struct Mansao* novo = (struct Mansao*) malloc(sizeof(struct Mansao));
    strcpy(novo->Nome_Comodo, valor);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Exploração da mansão
void Explorar_Comodo(struct Mansao* atual,  char visitas[][50], int *totalVisitas) {
    int escolha_jogador;

    // Registra o primeiro cômodo visitado
    strcpy(visitas[(*totalVisitas)++], atual->Nome_Comodo);

    while (1) {
        // Verifica se o comodo é sem saídas
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Você chegou a um cômodo sem saídas!\n");
            return;
        }

        printf("\nVocê está neste cômodo: %s\n", atual->Nome_Comodo);
        printf("Para onde quer ir?\n");
        printf("1 - Esquerda\n");
        printf("2 - Direita\n");
        printf("0 - Voltar\n");
        printf("Digite aqui: ");
        scanf("%d", &escolha_jogador);

        switch (escolha_jogador) {
        case 1: // Vai pelo caminho da esquerda
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
                printf("Você foi para: %s\n", atual->Nome_Comodo);
                strcpy(visitas[(*totalVisitas)++], atual->Nome_Comodo); // registra visita
            } else {
                printf("Não há cômodo à esquerda.\n");
            }
            break;

        case 2: // Vai pelo caminho da direita
            if (atual->direita != NULL) {
                atual = atual->direita;
                printf("Você foi para: %s\n", atual->Nome_Comodo);
                strcpy(visitas[(*totalVisitas)++], atual->Nome_Comodo); // registra visita
            } else {
                printf("Não há cômodo à direita.\n");
            }
            break;

        case 0: // Finaliza a exploração
            printf("Saindo da exploração...\n");
            return; 
            break;

        default:
            printf("Opção inválida! Tente novamente.\n");
            break;
        }
    }
}

// Função para liberar a memória da árvore
void liberar(struct Mansao* raiz) {
    if (raiz != NULL) {
        liberar(raiz->esquerda);
        liberar(raiz->direita);
        free(raiz);
    }
}

// Função principal
int main() {
    // Definindo os comodos da Mansão
    struct Mansao* raiz = criarComodo("Hall de Entrada");
    raiz->esquerda = criarComodo("Sala de Estar");
    raiz->direita = criarComodo("Biblioteca");
    raiz->esquerda->esquerda = criarComodo("Quarto");

    printf("Comodo principal: %s\n", raiz->Nome_Comodo);
    printf("Esquerda: %s\n", raiz->esquerda->Nome_Comodo);
    printf("Direita: %s\n", raiz->direita->Nome_Comodo);


    // Vetor para armazenar a sequência de salas visitadas
    char visitas[100][50];
    int totalVisitas = 0;

    // Exploração
    Explorar_Comodo(raiz, visitas, &totalVisitas);

    // Mostra a sequência de salas visitadas
    printf("\n--- Sequência de Cômodos Visitados ---\n");
    for (int i = 0; i < totalVisitas; i++) {
        printf("%d. %s\n", i + 1, visitas[i]);
    }

    // Libera memória
    liberar(raiz);

    return 0;
}
