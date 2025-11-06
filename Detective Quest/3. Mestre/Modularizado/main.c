#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "pistas.h"
#include "mansao.h"

//  Se tiver C instaldo no pc, abra o Terminal na pasta onde estão os arquivos e use isso no terminal para compilar: gcc main.c mansao.c pistas.c hash.c -o detectivequest.exe
// Função Principal Main
int main() {
    // Inicializa tabela hash vazia
    for (int i = 0; i < TAM_TAB_HASH; ++i) tabelaHash[i] = NULL;

    // Define os cômodos e pistas
    struct Mansao* raiz = criarComodo("Hall de Entrada", "Um bilhete rasgado com a letra A.");
    raiz->esquerda = criarComodo("Sala de Estar", "Uma chave dourada caída no sofá.");
    raiz->direita = criarComodo("Biblioteca", "Um livro com páginas arrancadas.");
    raiz->esquerda->esquerda = criarComodo("Quarto", "Um colar antigo sobre a cama.");

    // Associação pista → suspeito
    Inserir_Hash("Um bilhete rasgado com a letra A.", "Suspeito A");
    Inserir_Hash("Uma chave dourada caída no sofá.", "Suspeito B");
    Inserir_Hash("Um livro com páginas arrancadas.", "Suspeito C");
    Inserir_Hash("Um colar antigo sobre a cama.", "Suspeito B");

    // Controle de visitas e pistas
    char visitas[100][50];
    int totalVisitas = 0;
    struct PistaBST* arvorePistas = NULL;

    // Exploração
    Explorar_Comodo(raiz, visitas, &totalVisitas, &arvorePistas);

    // Exibição final
    printf("\n--- Sequência de Cômodos Visitados ---\n");
    for (int i = 0; i < totalVisitas; i++)
        printf("%d. %s\n", i + 1, visitas[i]);

    printf("\n--- Pistas Coletadas ---\n");
    exibirPistas(arvorePistas);

    // Verificação final
    char acusado[50];
    printf("\nQuem você acusa? Digite o nome do suspeito (Suspeito A, Suspeito B ou Suspeito C): ");
    int c; while ((c = getchar()) != '\n' && c != EOF);
    fgets(acusado, sizeof(acusado), stdin);
    acusado[strcspn(acusado, "\n")] = '\0';

    int matches = contarPistasDoSuspeito(arvorePistas, acusado);
    printf("\nPistas que apontam para '%s': %d\n", acusado, matches);
    if (matches >= 2)
        printf("Acusação aceita: há pistas suficientes para sustentar a acusação contra %s.\n", acusado);
    else
        printf("Acusação insuficiente: não há pistas suficientes contra %s.\n", acusado);

    liberarMansao(raiz);
    liberarPistas(arvorePistas);
    liberarHash();

    return 0;
}
