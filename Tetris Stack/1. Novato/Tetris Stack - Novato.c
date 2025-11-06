#include <stdio.h>
#include <stdlib.h>

#define MAX 5

//-----------------------------------------------------------------------------------------------------------
// Struct das Peças
typedef struct {
    char nome[2]; // Nome da peça, exemplo: I
    int id; // ID da peça, exemplo: 1
} Peca;

// Struct da Fila Circular
typedef struct {
    Peca itens[MAX]; // Vetor responsavel por guardar as informações das peças
    int inicio; // Indice do primeiro elemento da fila
    int fim; // Indice da próxima posição livre para inserir.
    int total; // quantidade atual de peças na fila.
} Fila;

// Função responsavel por inicializar a fila | “Zera” a fila, deixando-a vazia
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Função responsavel por inserir uma peça no final da Fila
void inserir_peca(Fila *f, Peca p) {
    // Verifica se há espaço
    if (f->total == MAX) {
        printf("Fila cheia. Não é possível inserir.\n");
        return;
    }
 
    f->itens[f->fim] = p;            // Coloca a peça no final
    f->fim = (f->fim + 1) % MAX;    // Move o fim (volta ao início se chegar ao final)
    f->total++;                     // Incrementa a contagem
}

// Função responsavel por remover uma peça no inicio da fila
void Jogar_peca(Fila *f, Peca *p) {
    if (f->total == 0) {
        printf("Fila vazia. Não é possível jogar.\n");
        return;
    }

    *p = f->itens[f->inicio];                // Copia o item do início para p    
    f->inicio = (f->inicio + 1) % MAX;       // Avança o início
    f->total--;                              // Diminui o total
}

// Função responsavel por mostrar a fila
void mostrar_pecas(Fila *f) {
    printf("Fila: ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%s, %d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("\n");
}
//-----------------------------------------------------------------------------------------------------------

// Função Principal main
int main(){
    int escolha_jogador;
    Fila f;
    inicializarFila(&f);  // Inicializa a fila
 
    // Insere algumas peças na fila
    Peca p1 = {"I", 1};
    Peca p2 = {"O", 2};
    Peca p3 = {"T", 3};
    Peca p4 = {"L", 4};
    Peca p5 = {"I", 5};

    inserir_peca(&f, p1);
    inserir_peca(&f, p2);
    inserir_peca(&f, p3);
    inserir_peca(&f, p4);
    inserir_peca(&f, p5);
 
    mostrar_pecas(&f);  // Mostra a fila
 
    do
    {
    printf("\nO que quer fazer?\n");
    printf("1-Jogar uma peça (remoçao)\n2-Inserir nova peça\n0-Sair\nDigite Aqui: ");
    scanf("%d", &escolha_jogador);

    switch (escolha_jogador)
    {
    case 1:
        // Remove uma pessoa da fila
        Peca removida;
        Jogar_peca(&f, &removida);  // Aqui usamos a função de remoção   
        printf("Peça removida: %s, %d\n", removida.nome, removida.id);
        mostrar_pecas(&f);  // Mostra a fila após a remoção
        break;
        
    case 2:
        Peca novaPeca;
        printf("Digite o nome da nova peça (ex: I, O, T, L): ");
        scanf("%s", novaPeca.nome);

        int idRepetido;
        do
        {
        
        idRepetido = 0;
        printf("Digite o ID da nova peça: ");
        scanf("%d", &novaPeca.id);

        // Verifica se o ID digitado é maior que 0
        if (novaPeca.id < 1)
        {
            printf("\nO Id da nova peça precisa ser maior que 0\n");
            continue;
        }
        
        for (int i = 0, idx = f.inicio; i < f.total; i++, idx = (idx + 1) % MAX) // idx = (idx + 1) % MAX || Incrementa o indice verficado e garante que o indice não vai passar do máximo
        {
            // Verifica o ID digitado é igual a algum que já existe
            if (f.itens[idx].id == novaPeca.id)
            {
                printf("\nJá existe uma peça com esse ID. ");
                idRepetido = 1;
                break;
            }
            
        }
    
        } while (novaPeca.id < 1 || idRepetido); // Se o ID estiver repetido vai pedir um novo id para o usuario

        inserir_peca(&f, novaPeca); // Adiciona na fila
        mostrar_pecas(&f);          // Mostra o resultado
        break;

    case 0:
        printf("Saindo do programa...\n");
        break;
        break;

    default:
        printf("Opção inválida!\n");
        break;
    }

    } while (escolha_jogador != 0);

    return 0;
}
