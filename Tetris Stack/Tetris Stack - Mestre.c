#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 5  
#define MAXP 3 

//-----------------------------------------------------------------------------------------------------------
// Struct das Peças
typedef struct {
    char nome[2]; // Nome da peça, exemplo: I
    int id;       // ID da peça, exemplo: 1
} Peca;

// Struct da Fila Circular
typedef struct {
    Peca itens[MAX]; // Vetor responsavel por guardar as informações das peças
    int inicio;      // Indice do primeiro elemento da fila
    int fim;         // Indice da próxima posição livre para inserir.
    int total;       // quantidade atual de peças na fila.
} Fila;

// Struct da Pilha
typedef struct {
    Peca itens[MAXP]; // Vetor das peças reservadas
    int topo;         // Índice do topo da pilha
} Pilha;

// Função responsavel por inicializar a fila | “Zera” a fila, deixando-a vazia
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Função responsável por inicializar a pilha
void inicializarPilha(Pilha *p) {
    p->topo = 0;
}

// Função que verifica se a pilha está cheia
int pilhaCheia(Pilha *p) {
    return p->topo == MAXP;
}

// Função que verifica se a pilha está vazia
int pilhaVazia(Pilha *p) {
    return p->topo == 0;
}

// Função que coloca uma peça no topo
void empilhar(Pilha *p, Peca nova) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia. Não é possível reservar mais peças.\n");
        return;
    }
    p->itens[p->topo++] = nova;
}

// Função que remove a peça do topo
Peca desempilhar(Pilha *p) {
    Peca removida = {"-", -1};
    if (pilhaVazia(p)) {
        printf("Pilha vazia. Nenhuma peça reservada.\n");
        return removida;
    }
    p->topo--;
    return p->itens[p->topo];
}

// Função responsavel por inserir uma peça no final da Fila
void inserir_peca(Fila *f, Peca p) {
    // Verifica se há espaço
    if (f->total == MAX) {
        printf("Fila cheia. Não é possível inserir.\n");
        return;
    }
 
    f->itens[f->fim] = p;           // Coloca a peça no final
    f->fim = (f->fim + 1) % MAX;    // Move o fim (volta ao início se chegar ao final)
    f->total++;                     // Incrementa a contagem
}

// Função responsavel por remover uma peça no inicio da fila
void Jogar_peca(Fila *f, Peca *p) {
    if (f->total == 0) {
        printf("Fila vazia. Não é possível jogar.\n");
        return;
    }

    *p = f->itens[f->inicio];       // Copia o item do início para p    
    f->inicio = (f->inicio + 1) % MAX;  // Avança o início
    f->total--;                         // Diminui o total
}

// Função que gera automaticamente uma nova peça
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[4][2] = {"I", "O", "T", "L"};
    int tipoAleatorio = rand() % 4; // Escolhe uma letra aleatória
    strcpy(nova.nome, tipos[tipoAleatorio]);
    nova.id = id;
    return nova;
}

// Função responsavel por mostrar a fila
void mostrar_pecas(Fila *f) {
    printf("Fila de Peças: ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%s, %d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("\n");
}

// Função responsavel por mostrar a pilha
void mostrar_pilha(Pilha *p) {
    printf("Pilha de Reserva (Topo -> Base): ");
    if (p->topo == 0) {
        printf("(vazia)");
    } else {
        for (int i = p->topo - 1; i >= 0; i--) {
            printf("[%s, %d] ", p->itens[i].nome, p->itens[i].id);
        }
    }
    printf("\n");
}

//-----------------------------------------------------------------------------------------------------------
// Função Principal main
int main(){
    srand( (unsigned) time(NULL) ); // Para gerar peças aleatórias
    int escolha_jogador;
    int proximoID = 6; // Próximo ID a ser gerado

    Fila f;
    Pilha p;
    inicializarFila(&f);  // Inicializa a fila
    inicializarPilha(&p); // Inicializa a pilha
 
    // Insere algumas peças na fila
    inserir_peca(&f, (Peca){"I", 1});
    inserir_peca(&f, (Peca){"O", 2});
    inserir_peca(&f, (Peca){"T", 3});
    inserir_peca(&f, (Peca){"L", 4});
    inserir_peca(&f, (Peca){"I", 5});
 
    mostrar_pecas(&f);  // Mostra a fila
    mostrar_pilha(&p);  // Mostra a pilha
 
    do {
        printf("\nO que quer fazer?\n");
        printf("1-Jogar uma peça (remoção)\n2-Reservar peça\n3-Exibir estado atual\n4-Trocar peça atual (fila <-> pilha)\n5-Troca múltipla\n0-Sair\nDigite Aqui: ");
        scanf("%d", &escolha_jogador);

        switch (escolha_jogador) {
        case 1: {
            // Remove uma peça da fila
            Peca removida;
            Jogar_peca(&f, &removida);
            printf("\nPeça jogada: %s, %d\n", removida.nome, removida.id);

            // Gera nova peça automaticamente
            Peca nova = gerarPeca(proximoID++);
            inserir_peca(&f, nova);
            break;
        }

        case 2: {
            // Move a peça da frente da fila para a pilha reserva
            if (f.total == 0) {
                printf("Fila vazia. Não é possível reservar.\n");
                break;
            }
            if (pilhaCheia(&p)) {
                printf("Pilha cheia! Não é possível reservar mais peças.\n");
                break;
            }

            Peca reservada;
            Jogar_peca(&f, &reservada); // Retira da fila
            empilhar(&p, reservada);    // Coloca na pilha
            printf("\nPeça reservada: %s, %d\n", reservada.nome, reservada.id);

            // Gera nova peça automaticamente
            Peca nova = gerarPeca(proximoID++);
            inserir_peca(&f, nova);
            break;
        }

        case 3: 
            // Mostra o estado atual
            mostrar_pecas(&f);
            mostrar_pilha(&p);
            break;

        case 4: {
            // Troca: inicio da fila <-> topo da pilha
            if (f.total == 0) {
                printf("\nFila vazia. Não há peça para trocar.\n");
                break;
            }
            if (pilhaVazia(&p)) {
                printf("\nPilha vazia. Nenhuma peça para trocar.\n");
                break;
            }

            int idxFila = f.inicio;
            int idxPilha = p.topo - 1;
            Peca temp = f.itens[idxFila];
            f.itens[idxFila] = p.itens[idxPilha];
            p.itens[idxPilha] = temp;

            printf("\nTroca realizada (inicio da fila <-> topo da pilha).\n");
            break;
        }

        case 5: {
            // Troca múltipla: 3 primeiras peças da fila ↔ 3 da pilha
            if (f.total < 3 || p.topo < 3) {
                printf("\nNão há peças suficientes para a troca múltipla (mínimo 3 em cada).\n");
                break;
            }

            // salva temporariamente as 3 primeiras da fila (na ordem 0..2)
            Peca filaTemp[3];
            for (int i = 0; i < 3; i++) {
                int idxFila = (f.inicio + i) % MAX;
                filaTemp[i] = f.itens[idxFila];
            }

            // salva temporariamente as 3 do topo da pilha (Topo -> base)
            Peca pilhaTemp[3];
            for (int i = 0; i < 3; i++) {
                pilhaTemp[i] = p.itens[p.topo - 1 - i]; 
            }

            // coloca as 3 da pilha (Topo->base) nas 3 primeiras posições da fila (na mesma ordem)
            for (int i = 0; i < 3; i++) {
                int idxFila = (f.inicio + i) % MAX;
                f.itens[idxFila] = pilhaTemp[i]; 
            }

            // coloca as 3 da fila na pilha, invertendo a ordem para que fila[0] vire base e fila[2] vire topo
            for (int i = 0; i < 3; i++) {
                int idxPilha = p.topo - 1 - i;    
                p.itens[idxPilha] = filaTemp[2 - i];
            }
            mostrar_pecas(&f);
            mostrar_pilha(&p);
            break;
        }

        case 0:
            printf("Saindo do programa...\n");
            break;

        default:
            printf("Opção inválida!\n");
            break;
        }

        // Mostra o estado atual quando o jogador escolhe opções diferente de 3 e de 5
        if (escolha_jogador != 5 && escolha_jogador != 3) {
            mostrar_pecas(&f);
            mostrar_pilha(&p);
        }

    } while (escolha_jogador != 0);

    return 0;
}