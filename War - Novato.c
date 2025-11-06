#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 30
#define MAX_COR 10

// Struct do territorio
struct TERRITORIO
{
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int numero_tropas;
};

// Função usada para limpar o buffer e evitar erros ao usar scanf e depois fgets
void Limpar_Buffer_Entrada(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
};

int main(){

    struct TERRITORIO territorios[5]; // territorio é o vetor em que está armazenado as infos de cada territorio
    int numero_de_cadastros = 0;

    printf("=============================================\n");
    printf("Cadastro de Territórios\n");
    printf("=============================================\n");

    do // Loop dos 5 cadastros
    {
         // Cadastro de Territorios
    printf("----------------------------------------------\n");
    printf("TERRITÓRIO %d\n", numero_de_cadastros+1);

    printf("Digite o nome do Território:");
    fgets(territorios[numero_de_cadastros].nome, MAX_NOME, stdin);

    printf("Digite a cor do Território:");
    fgets(territorios[numero_de_cadastros].cor, MAX_COR, stdin);

    territorios[numero_de_cadastros].nome[strcspn(territorios[numero_de_cadastros].nome, "\n")] = '\0'; // Faz com que o '\n' automatio do fgets não aconteça, assim evitando erros
    territorios[numero_de_cadastros].cor[strcspn(territorios[numero_de_cadastros].cor, "\n")] = '\0';

    printf("Digite o número de tropas:");
    scanf("%d", &territorios[numero_de_cadastros].numero_tropas);
    Limpar_Buffer_Entrada(); // Limpa o buffer para evitar erros com o fgets

    printf("----------------------------------------------\n\n");
    numero_de_cadastros++; // Incrementa o numero de cadastros até chegar em 5, que são representados respectivamente como 0, 1, 2, 3, 4 no vetor

    } while (numero_de_cadastros < 5);

    // Pausa até que seja pressioando enter
    printf("Pressione enter para Ver os Territorios do Mapa...\n\n");
    getchar(); // Responsável pela pausa

    printf("=============================================\n");
    printf("TERRITÓRIOS DO MAPA\n");
    printf("=============================================\n");

    for (int i = 0; i < 5; i++) // Loop que mostra os 5 Territorios cadastrados
    {
        printf("----------------------------------------------\n");

        printf("Território %d\n", i+1);
        printf("- Nome do Território: %s\n", territorios[i].nome);
        printf("- Dominado por: Exercito %s\n", territorios[i].cor);
        printf("- Quantidade de Tropas: %d\n", territorios[i].numero_tropas);

        printf("----------------------------------------------\n\n");
    }
    return 0;
}