#include "funcoes.h"

// Se tiver C instaldo no pc, abra o Terminal na pasta onde estão os arquivos e use isso no terminal para compilar: gcc main.c funcoes.c -o jogo.exe
// Função Principal
int main(){
    srand((unsigned int)time(NULL));
    int numero_Territorios;

    do {
        printf("Quantos Territórios o jogo vai ter?");
        scanf("%d", &numero_Territorios);
        Limpar_Buffer_Entrada();

        if (numero_Territorios > 1) {
            break;
        } else {
            printf("O jogo só pode acontecer se tiver 2 ou mais Territorios.\n\n");
        }

    } while (1);

    struct TERRITORIO *territorios;
    int numero_de_cadastros = 0;
    int escolha_usuario;
    territorios = (struct TERRITORIO*) calloc(numero_Territorios, sizeof(struct TERRITORIO));
    int atacante;
    int defensor;

    // Inicializa missao pointer pra NULL
    for (int i = 0; i < numero_Territorios; i++) territorios[i].missao = NULL;

    printf("\n=============================================\n");
    printf("Cadastro de Territórios\n");
    printf("=============================================\n");

    // Cadastro dos territorios
    do 
    {
        printf("----------------------------------------------\n");
        printf("TERRITÓRIO %d\n", numero_de_cadastros+1);

        printf("Digite o nome do Território:");
        fgets(territorios[numero_de_cadastros].nome, MAX_NOME, stdin);

        printf("Digite a cor do Território:");
        fgets(territorios[numero_de_cadastros].cor, MAX_COR, stdin);

        territorios[numero_de_cadastros].nome[strcspn(territorios[numero_de_cadastros].nome, "\n")] = '\0';
        territorios[numero_de_cadastros].cor[strcspn(territorios[numero_de_cadastros].cor, "\n")] = '\0';

        do {
            printf("Digite o número de tropas:");
            scanf("%d", &territorios[numero_de_cadastros].numero_tropas);

            if (territorios[numero_de_cadastros].numero_tropas > 0) {
                break;
            } else {
                printf("\nDigite só é permitido 1 ou mais tropas\n\n");
            }
        } while (1);

        Limpar_Buffer_Entrada();

        printf("----------------------------------------------\n\n");
        numero_de_cadastros++;

    } while (numero_de_cadastros < numero_Territorios);

    // Após cadastrar territorios, vamos construir as missões
    // 1) Coletar cores únicas cadastradas para permitir o sorteio de uma cor para a missão "Eliminar todas as tropas da cor {cor}"
    char coresUnicas[100][MAX_COR]; // sufixo suficiente para cores
    int qtdCores = 0;
    for (int i = 0; i < numero_Territorios; i++) {
        int existe = 0;
        for (int j = 0; j < qtdCores; j++) {
            if (strcmp(coresUnicas[j], territorios[i].cor) == 0) { existe = 1; break; }
        }
        if (!existe) {
            strncpy(coresUnicas[qtdCores], territorios[i].cor, MAX_COR-1);
            coresUnicas[qtdCores][MAX_COR-1] = '\0';
            qtdCores++;
        }
    }

    // Vetor de templates de missão (um deles contém placeholder {cor})
    char *missoes_templates[TOTAL_MISSOES] = {
        "Conquistar 1 territorio inimigo",
        "Eliminar todas as tropas da cor {cor}",
        "Sobreviver com pelo menos 3 territorios ativos",
        "Reduzir as tropas inimigas de um territorio a zero",
        "Seu territorio ter pelo menos 3 tropas"
    };

    // Criar vetor de strings finais (substituindo {cor} por uma cor sorteada entre as cadastradas)
    char *missoes_finais[TOTAL_MISSOES];
    for (int i = 0; i < TOTAL_MISSOES; i++) {
        // se template contém {cor}, substitui por cor aleatória entre as cadastradas
        if (strstr(missoes_templates[i], "{cor}") != NULL) {
            char temp[128];
            if (qtdCores > 0) {
                char *corEscolhida = coresUnicas[rand() % qtdCores];
                snprintf(temp, sizeof(temp), "Eliminar todas as tropas da cor %s", corEscolhida);
            } else {
                // fallback: se não houver cores (não deve acontecer), escolhe "AZUL"
                snprintf(temp, sizeof(temp), "Eliminar todas as tropas da cor %s", "AZUL");
            }
            missoes_finais[i] = (char*) malloc(strlen(temp) + 1);
            strcpy(missoes_finais[i], temp);
        } else {
            missoes_finais[i] = (char*) malloc(strlen(missoes_templates[i]) + 1);
            strcpy(missoes_finais[i], missoes_templates[i]);
        }
    }

    // Atribuir missões a cada território (cada território representa um "jogador" aqui)
    for (int i = 0; i < numero_Territorios; i++) {
        // aloca memória para a missão do território (armazenamento dinâmico)
        territorios[i].missao = (char*) malloc(128); // espaço suficiente para a missão
        atribuirMissao(territorios[i].missao, missoes_finais, TOTAL_MISSOES);
    }

    // Pausa até que seja pressioando enter
    printf("Pressione enter para Ver os Territorios do Mapa...\n\n");
    getchar();

    printf("=============================================\n");
    printf("TERRITÓRIOS DO MAPA\n");
    printf("=============================================\n");

   for (int i = 0; i < numero_Territorios; i++)
{
    printf("----------------------------------------------\n");
    printf("Território %d\n", i+1);
    printf("- Nome do Território: %s\n", territorios[i].nome);
    printf("- Dominado por: Exercito %s\n", territorios[i].cor);
    printf("- Quantidade de Tropas: %d\n", territorios[i].numero_tropas);
    printf("- Missão atribuída: %s\n", territorios[i].missao);

    // Verificação e exibição do status da missão
    int status = verificarMissao(territorios[i].missao, territorios, numero_Territorios);
    if (status)
        printf("- Status da Missão: ✅ COMPLETA\n");
    else
        printf("- Status da Missão: ❌ INCOMPLETA\n");

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

        if (escolha_usuario == 0) {
            break;
        }

        // Loop Responsavel pelo Andamento do Jogo
        do
        {
            printf("\n\n---- Fase de Ataque ----\n");
            printf("Digite o Território Atacante (1 a %d): ", numero_Territorios);
            scanf("%d", &atacante);
            printf("Digite o Território Defensor (1 a %d): ", numero_Territorios);
            scanf("%d", &defensor);

            if ((atacante < 1 || atacante > numero_Territorios) || (defensor < 1 || defensor > numero_Territorios)) {
                printf("\nNão é possível escolher um Território que não existe!\n");
            } else if (atacante == defensor) {
                printf("\nVocê não pode se atacar, escolha Territórios diferentes!\n");
            } else if (territorios[atacante-1].numero_tropas == 0 || territorios[defensor-1].numero_tropas == 0) {
                printf("\nNão é possível escolher um Território Derrotado (Sem Tropas)!\n");
            } else {
                break;
            }

        } while (1);

        Combate(atacante, defensor, territorios[atacante-1].nome, territorios[defensor-1].nome, &territorios[atacante-1].numero_tropas, &territorios[defensor-1].numero_tropas, territorios[atacante-1].cor, territorios[defensor-1].cor);

        // Verifica missões de cada jogador ao final do turno
        for (int i = 0; i < numero_Territorios; i++) {
            if (territorios[i].missao != NULL) {
                if (verificarMissao(territorios[i].missao, territorios, numero_Territorios)) {
                    printf("\n=============================================\n");
                    printf("MISSÃO CUMPRIDA!\n");
                    printf("Território %s (Exército %s) cumpriu a missão: %s\n", territorios[i].nome, territorios[i].cor, territorios[i].missao);
                    printf("Vencedor: Território %s (Exército %s)\n", territorios[i].nome, territorios[i].cor);
                    printf("=============================================\n");
                    // liberar memória antes de sair
                    for (int k = 0; k < TOTAL_MISSOES; k++) {
                        free(missoes_finais[k]);
                    }
                    for (int k = 0; k < numero_Territorios; k++) {
                        if (territorios[k].missao) free(territorios[k].missao);
                    }
                    free(territorios);
                    return 0;
                }
            }
        }

        // Verifica se se 4 territorios foram derrotados (lógica original)
        if (
            (numero_Territorios >= 5 &&
            (
            (territorios[0].numero_tropas == 0 && territorios[1].numero_tropas == 0 && territorios[2].numero_tropas == 0 && territorios[3].numero_tropas == 0) ||
            (territorios[1].numero_tropas == 0 && territorios[2].numero_tropas == 0 && territorios[3].numero_tropas == 0 && territorios[4].numero_tropas == 0) ||
            (territorios[0].numero_tropas == 0 && territorios[2].numero_tropas == 0 && territorios[3].numero_tropas == 0 && territorios[4].numero_tropas == 0) ||
            (territorios[0].numero_tropas == 0 && territorios[1].numero_tropas == 0 && territorios[3].numero_tropas == 0 && territorios[4].numero_tropas == 0) ||
            (territorios[0].numero_tropas == 0 && territorios[1].numero_tropas == 0 && territorios[2].numero_tropas == 0 && territorios[4].numero_tropas == 0)
            ))
            )
        {
            for (int i = 0; i < numero_Territorios; i++)
            {
                if (territorios[i].numero_tropas != 0)
                {
                    printf("\nO Território %s (%s) é o Vencedor!\n", territorios[i].cor, territorios[i].nome);
                }
            }

            break;
        }

    } while (escolha_usuario != 0);

    // Limpar e liberar memórias alocadas
    for (int k = 0; k < TOTAL_MISSOES; k++) {
        free(missoes_finais[k]);
    }
    for (int k = 0; k < numero_Territorios; k++) {
        if (territorios[k].missao) free(territorios[k].missao);
    }
    free(territorios);

    printf("\nJogo Finalizado.\n\n");

    return 0;
}