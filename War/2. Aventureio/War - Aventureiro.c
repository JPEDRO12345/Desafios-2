#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

// Função que mostra o estado do exercito / Estado do Mapa
void Mapa_Completo(int i, char *nome, char *cor, int tropas) {
    printf("%d. %s (Exército %s, Tropas: %d)\n", i+1, nome, cor, tropas);
}

// Função de Combate
void Combate(int territorio_atacante, int territorio_defensor, char *nome_atacante, char *nome_defensor, int *tropa_atacante, int *tropa_defensora, char *cor_atacante, char *cor_defensor)
{
    // Variaveis reponsaveis por capturar um numero aleatorio entre 1 e 6
     int dado_atacante = (rand() % 6) + 1;
     int dado_defensor = (rand() % 6) + 1;

     printf("\nLançamento dos dados:\n");
     printf("Território %d (%s) - %d\n", territorio_atacante, nome_atacante, dado_atacante);
     printf("Território %d (%s) - %d\n", territorio_defensor, nome_defensor, dado_defensor);

     // Verifica quem venceu ou se ocorreu um empate
     if (dado_atacante > dado_defensor) {// Verifica se o Atacante Venceu
        printf("\nO Território %d (%s) Venceu o Território %d (%s)!\n", territorio_atacante, nome_atacante, territorio_defensor, nome_defensor);
        (*tropa_defensora)--; // O Território Derrotado Perde 1 Tropa

        if (*tropa_defensora == 0) // Se o derritorio defensor for derrotado, o defensor receberar a cor do territorio atacante
        {
            strcpy(cor_defensor, cor_atacante);
        }
        
     } else if (dado_atacante < dado_defensor) { // Verifica se o Defensor Venceu
        printf("\nO Território %d (%s) Venceu o Território %d (%s)!\n", territorio_defensor, nome_defensor, territorio_atacante, nome_atacante);
        (*tropa_atacante)--;

        if (*tropa_atacante == 0) // Se o derritorio defensor for derrotado, o defensor receberar a cor do territorio atacante
        {
            strcpy(cor_atacante, cor_defensor); // O Território Derrotado Perde 1 Tropa
        }

     } else { // Se Ninguém vencer, ocorre empate e ambos perdem uma tropa
        printf("\nEmpate!\n");
        (*tropa_atacante)--;
        (*tropa_defensora)--;
     }
}

int main(){
    srand(time(NULL)); // Responsavel por gerar numero aleatorio entre de 1 a 6, simulando a dinâmica de um Dado
    int numero_Territorios;

    do //Faz com que tenha pelo menos 2 Territorios
    {
    printf("Quantos Territórios o jogo vai ter?");
    scanf("%d", &numero_Territorios);
    Limpar_Buffer_Entrada();

    if (numero_Territorios > 1) // Verifica se os numeros de territorios escolhido é maior que 1
    {
        break;
    } else {
        printf("O jogo só pode acontecer se tiver 2 ou mais Territorios.\n\n");
    }
    
    } while (1);

    struct TERRITORIO *territorios; // territorio é o ponteiro que aponta para TERRITORIO
    int numero_de_cadastros = 0;
    int escolha_usuario;
    territorios = (struct TERRITORIO*) calloc(numero_Territorios, sizeof(struct TERRITORIO));
    int atacante;
    int defensor;

    printf("\n=============================================\n");
    printf("Cadastro de Territórios\n");
    printf("=============================================\n");

    // Loop dos 5 cadastros
    do 
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

     do // Só permite que o usuario prossiga caso o numero de tropas seja positivo
        {
            printf("Digite o número de tropas:");
            scanf("%d", &territorios[numero_de_cadastros].numero_tropas);

            if (territorios[numero_de_cadastros].numero_tropas > 0) // Verifica se tem 1 ou mais tropas
            {
                break;
            } else {
                printf("\nDigite só é permitido 1 ou mais tropas\n\n");
            }
            } while (1);

    Limpar_Buffer_Entrada(); // Limpa o buffer para evitar erros com o fgets

    printf("----------------------------------------------\n\n");
    numero_de_cadastros++; // Incrementa o numero de cadastros até chegar em 5, que são representados respectivamente como 0, 1, 2, 3, 4 no vetor

    } while (numero_de_cadastros < numero_Territorios);

    // Pausa até que seja pressioando enter
    printf("Pressione enter para Ver os Territorios do Mapa...\n\n");
    getchar(); // Responsável pela pausa

    printf("=============================================\n");
    printf("TERRITÓRIOS DO MAPA\n");
    printf("=============================================\n");

    for (int i = 0; i < numero_Territorios; i++) // Loop que mostra os 5 Territorios cadastrados
    {
        printf("----------------------------------------------\n");
        printf("Território %d\n", i+1);
        printf("- Nome do Território: %s\n", territorios[i].nome);
        printf("- Dominado por: Exercito %s\n", territorios[i].cor);
        printf("- Quantidade de Tropas: %d\n", territorios[i].numero_tropas);
        printf("----------------------------------------------\n\n");
    }

    // Loop principal da batalha
    do
    {   
        // Loop que mostra o Estado do Mapa
        for (int i = 0; i < numero_Territorios; i++)
    {
        Mapa_Completo(i,territorios[i].nome, territorios[i].cor, territorios[i].numero_tropas);
    }

    printf("\nO quer fazer?\n");
    printf("1- Atacar\n");
    printf("0- Sair\n");
    printf("Digite aqui: ");
    scanf("%d", &escolha_usuario);

    if (escolha_usuario == 0) // Verifica se o usuario digitou para sair
    {
        break;
    }

    // Loop Responsavel pelo Andamento do Jogo
    do 
    {
    
    // Escolha de Territorios no combate
    printf("\n\n---- Fase de Ataque ----\n");
    printf("Digite o Território Atacante (1 a %d): ", numero_Territorios);
    scanf("%d", &atacante);
    printf("Digite o Território Defensor (1 a %d): ", numero_Territorios);
    scanf("%d", &defensor);

    if ((atacante < 1 || atacante > numero_Territorios) || (defensor < 1 || defensor > numero_Territorios)) { // Verifica se o Territorio existe
    printf("\nNão é possível escolher um Território que não existe!\n");

    } else if (atacante == defensor) { // Verifica se um Territorio está atacando ele mesmo 
    printf("\nVocê não pode se atacar, escolha Territórios diferentes!\n");

    } else if (territorios[atacante-1].numero_tropas == 0 || territorios[defensor-1].numero_tropas == 0) { // Verifica se foi escolhido um Territorio derrotado
    printf("\nNão é possível escolher um Território Derrotado (Sem Tropas)!\n");

    } else {
        break; // Sai do loop se o atacante e o defensor existirem, se forem diferentes e se nenhum dos territorios tiver 0 Tropas
    }
    
    } while (1);

    Combate(atacante, defensor, territorios[atacante-1].nome, territorios[defensor-1].nome, &territorios[atacante-1].numero_tropas, &territorios[defensor-1].numero_tropas, territorios[atacante-1].cor, territorios[defensor-1].cor); // Chamada da Função Responsavel pelo Combate

    // Verifica se se 4 territorios foram derrotados
    if (
        (territorios[0].numero_tropas == 0 && territorios[1].numero_tropas == 0 && territorios[2].numero_tropas == 0 && territorios[3].numero_tropas == 0) || // Se o Territorio 5 (4 no indice) ganhar
        (territorios[1].numero_tropas == 0 && territorios[2].numero_tropas == 0 && territorios[3].numero_tropas == 0 && territorios[4].numero_tropas == 0) || // Se o Territorio 1 (0 no indice) ganhar
        (territorios[0].numero_tropas == 0 && territorios[2].numero_tropas == 0 && territorios[3].numero_tropas == 0 && territorios[4].numero_tropas == 0) || // Se o Territorio 2 (1 no indice) ganhar
        (territorios[0].numero_tropas == 0 && territorios[1].numero_tropas == 0 && territorios[3].numero_tropas == 0 && territorios[4].numero_tropas == 0) || // Se o Territorio 3 (2 no indice) ganhar
        (territorios[0].numero_tropas == 0 && territorios[1].numero_tropas == 0 && territorios[2].numero_tropas == 0 && territorios[4].numero_tropas == 0) // Se o Territorio 4 (3 no indice) ganhar 
        )
    {
        // Loop que captura as informações dos 5 territorios
        for (int i = 0; i < numero_Territorios; i++)
        {
            // Verifica qual Territorio saiu Vencedor
            if (territorios[i].numero_tropas != 0)
            {
                printf("\nO Território %s (%s) é o Vencedor!\n", territorios[i].cor, territorios[i].nome);
            }
            
        }

        break; // Terminar Jogo
        
    }

    } while (escolha_usuario != 0);

    free(territorios); // Liberando memoria

    printf("\nJogo Finalizado.\n\n");

    return 0;
}
