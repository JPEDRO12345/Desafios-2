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

// Tabela Hash para mapear pista -> suspeito
// Encadeamento simples | Tamanho fixo da tabela
#define TAM_TAB_HASH 101
// Representa um elemento (nó) da tabela hash responsável por associar uma pista específica a um suspeito
typedef struct AssociacaoPistaSuspeito {
    char chave[100];         // pista (key)
    char suspeito[50];       // suspeito (value)
    struct AssociacaoPistaSuspeito* prox;
} AssociacaoPistaSuspeito;

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

    int cmp = strcmp(texto, raiz->pista);
    if (cmp < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, texto);
    else if (cmp > 0)
        raiz->direita = inserirPista(raiz->direita, texto);
    // se igual, não insere duplicata (mantemos única)
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

// Função auxiliar: percorre BST e conta quantas pistas apontam para 'suspeito'
// usa Buscar_Pista_Sus para encontrar quem está associado a cada pista
int contarPistasDoSuspeito_helper(struct PistaBST* raiz, const char* suspeito) {
    if (raiz == NULL) return 0;
    int count = 0;
    // percorre esquerda
    count += contarPistasDoSuspeito_helper(raiz->esquerda, suspeito);
    // verifica esta pista
    const char* s = Buscar_Pista_Sus(raiz->pista);
    if (s != NULL && strcmp(s, suspeito) == 0) count++;
    // percorre direita
    count += contarPistasDoSuspeito_helper(raiz->direita, suspeito);
    return count;
}

int contarPistasDoSuspeito(struct PistaBST* raiz, const char* suspeito) {
    return contarPistasDoSuspeito_helper(raiz, suspeito);
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
        if (scanf("%d", &escolha_jogador) != 1) {
            // entrada inválida: limpa stdin e continua
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Entrada inválida. Tente novamente.\n");
            continue;
        }

        switch (escolha_jogador) {
        case 1: // Vai para a esquerda
            if (atual->esquerda != NULL) {
                caminho[topo++] = atual;  // empilha o cômodo atual
                atual = atual->esquerda;
                printf("Você foi para: %s\n", atual->Nome_Comodo);
                strcpy(visitas[(*totalVisitas)++], atual->Nome_Comodo); // registra visita
                printf("Você encontrou uma pista: %s\n", atual->Pista);
                *arvorePistas = inserirPista(*arvorePistas, atual->Pista); // insere a nova pista na árvore
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
                *arvorePistas = inserirPista(*arvorePistas, atual->Pista); // insere a nova pista na árvore
            } else {
                printf("Não há cômodo à direita.\n");
            }
            break;

        case 0: // Voltar
            if (topo == 0) {
                // Se está na raiz -> encerra
                printf("Você está no Hall de Entrada. Encerrando exploração...\n");
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
    // Inicializa tabela hash vazia
    for (int i = 0; i < TAM_TAB_HASH; ++i) tabelaHash[i] = NULL;

    // Definindo os comodos da Mansão com pistas
    struct Mansao* raiz = criarComodo("Hall de Entrada", "Um bilhete rasgado com a letra A.");
    raiz->esquerda = criarComodo("Sala de Estar", "Uma chave dourada caída no sofá.");
    raiz->direita = criarComodo("Biblioteca", "Um livro com páginas arrancadas.");
    raiz->esquerda->esquerda = criarComodo("Quarto", "Um colar antigo sobre a cama.");

    // Definindo a associação pista -> suspeito na tabela hash
    Inserir_Hash("Um bilhete rasgado com a letra A.", "Suspeito A");
    Inserir_Hash("Uma chave dourada caída no sofá.", "Suspeito B");
    Inserir_Hash("Um livro com páginas arrancadas.", "Suspeito C");
    Inserir_Hash("Um colar antigo sobre a cama.", "Suspeito B");

    // Vetor para armazenar a sequência de salas visitadas
    char visitas[100][50];
    int totalVisitas = 0;

    // Árvore de pistas (BST)
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

    // Pergunta ao jogador quem é o culpado
    char acusado[50];
    printf("\nQuem você acusa? Digite o nome do suspeito (Suspeito A, Suspeito B ou Suspeito C): ");
    // lê uma linha 
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // limpa buffer
    if (fgets(acusado, sizeof(acusado), stdin) != NULL) {
        // remove newline
        acusado[strcspn(acusado, "\n")] = '\0';
    }

    // Verifica se pelo menos duas pistas apontam para o acusado
    int matches = contarPistasDoSuspeito(arvorePistas, acusado);
    printf("\nPistas que apontam para '%s': %d\n", acusado, matches);
    if (matches >= 2) {
        printf("Acusação aceita: há pistas suficientes para sustentar a acusação contra %s.\n", acusado);
    } else {
        printf("Acusação insuficiente: não há pistas suficientes contra %s.\n", acusado);
    }

    // Libera memória
    liberarMansao(raiz);
    liberarPistas(arvorePistas);
    liberarHash();

    return 0;
}