#include "funcoes.h"

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
     int dado_atacante = (rand() % 6) + 1;
     int dado_defensor = (rand() % 6) + 1;

     printf("\nLançamento dos dados:\n");
     printf("Território %d (%s) - %d\n", territorio_atacante, nome_atacante, dado_atacante);
     printf("Território %d (%s) - %d\n", territorio_defensor, nome_defensor, dado_defensor);

     if (dado_atacante > dado_defensor) {
        printf("\nO Território %d (%s) Venceu o Território %d (%s)!\n", territorio_atacante, nome_atacante, territorio_defensor, nome_defensor);
        (*tropa_defensora)--;

        if (*tropa_defensora == 0) {
            strcpy(cor_defensor, cor_atacante);
            *tropa_atacante += 2; // +2 tropas para o território vencedor
        }

     } else if (dado_atacante < dado_defensor) {
        printf("\nO Território %d (%s) Venceu o Território %d (%s)!\n", territorio_defensor, nome_defensor, territorio_atacante, nome_atacante);
        (*tropa_atacante)--;

        if (*tropa_atacante == 0) {
            strcpy(cor_atacante, cor_defensor);
            *tropa_defensora += 2; // +2 tropas para o território vencedor
        }

     } else {
        printf("\nEmpate!\n");
        (*tropa_atacante)--;
        (*tropa_defensora)--;
     }
}

// Função que sorteia uma missão e copia para destino usando strcpy
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    strcpy(destino, missoes[idx]);
}

// Função auxiliar: conta quantos territorios têm determinada cor e (opcional) com tropas>0
int contarTerritoriosPorCor(struct TERRITORIO* mapa, int tamanho, const char* cor, int apenasComTropas) {
    int cont = 0;
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].cor, cor) == 0) {
            if (!apenasComTropas || (apenasComTropas && mapa[i].numero_tropas > 0)) cont++;
        }
    }
    return cont;
}

// Função que verifica se a missão foi cumprida.
int verificarMissao(char* missao, struct TERRITORIO* mapa, int tamanho) {
    // encontra o índice do proprietário consultando as missões dos territórios
    int dono = -1;
    for (int i = 0; i < tamanho; i++) {
        if (mapa[i].missao != NULL && strcmp(mapa[i].missao, missao) == 0) {
            dono = i;
            break;
        }
    }
    if (dono == -1) return 0; // missão não encontrada entre os jogadores

    // Verificação de missão
    if (strstr(missao, "Conquistar 1 territorio inimigo") != NULL) {
        int qtd = contarTerritoriosPorCor(mapa, tamanho, mapa[dono].cor, 0);
        if (qtd > 1) return 1;
        return 0;
    }

    if (strstr(missao, "Eliminar todas as tropas da cor") != NULL) {
        char *ptr = strstr(missao, "Eliminar todas as tropas da cor");
        if (ptr) {
            char copia[128];
            strncpy(copia, missao, sizeof(copia)-1);
            copia[sizeof(copia)-1] = '\0';
            char *token = strrchr(copia, ' ');
            if (token) {
                char corAlvo[MAX_COR];
                strncpy(corAlvo, token+1, MAX_COR-1);
                corAlvo[MAX_COR-1] = '\0';
                for (int i = 0; i < tamanho; i++) {
                    if (strcmp(mapa[i].cor, corAlvo) == 0 && mapa[i].numero_tropas > 0) {
                        return 0;
                    }
                }
                return 1;
            }
        }
        return 0;
    }

    if (strstr(missao, "Sobreviver com pelo menos 3 territorios ativos") != NULL) {
        int qtd = contarTerritoriosPorCor(mapa, tamanho, mapa[dono].cor, 1);
        if (qtd >= 3) return 1;
        return 0;
    }

    if (strstr(missao, "Reduzir as tropas inimigas de um territorio a zero") != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, mapa[dono].cor) != 0 && mapa[i].numero_tropas == 0) {
                return 1;
            }
        }
        return 0;
    }

    if (strstr(missao, "Seu territorio ter pelo menos 3 tropas") != NULL) {
        if (mapa[dono].numero_tropas >= 3) return 1;
        return 0;
    }

    return 0;
}