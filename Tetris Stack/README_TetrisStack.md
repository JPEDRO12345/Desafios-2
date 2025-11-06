# 🧱 Tetris Stack -- Estruturas de Dados em C

O **Tetris Stack** é um projeto desenvolvido em **linguagem C** que
simula o controle de peças do clássico jogo **Tetris**, utilizando
**estruturas de dados fundamentais** --- como **filas circulares** e
**pilhas** --- para representar o comportamento de peças futuras e
reservadas.\
Este projeto foi criado como parte da disciplina de **Estrutura de Dados** na **Estácio**, com o objetivo de exercitar o raciocínio
lógico e a aplicação prática de estruturas de controle.

------------------------------------------------------------------------

## 📌 Objetivos por Nível

### 🧩 Nível Novato

Neste nível, o jogador gerencia apenas a **fila de peças futuras**,
representando a sequência de blocos que cairão no jogo.

#### Funcionalidades

-   Inicializar a **fila de peças** com tamanho fixo (ex: 5 peças).\
-   Permitir as ações:
    -   **Jogar peça (dequeue):** remove a peça da frente da fila.\
    -   **Inserir nova peça (enqueue):** adiciona uma nova peça ao final
        da fila.\
    -   **Exibir fila:** mostra todas as peças atuais na fila com seus
        tipos e identificadores.
-   Gerar automaticamente as peças com a função `gerarPeca()`, que
    sorteia um tipo (`I`, `O`, `T`, `L`) e um id numérico.

#### Estrutura da Peça

``` c
typedef struct {
    char nome[2]; // Tipo da peça ('I', 'O', 'T', 'L')
    int id;       // Identificador único
} Peca;
```

#### Conceitos Trabalhados

-   **Fila circular** e manipulação de índices (`início`, `fim`,
    `total`)
-   **Structs e arrays**
-   **Funções e modularização**
-   **Entrada e saída via terminal**

------------------------------------------------------------------------

### ⚙️ Nível Aventureiro

O sistema passa a integrar **fila** e **pilha**, simulando a mecânica de
**reservar peças**.

#### Funcionalidades

-   Manter uma **fila circular** de 5 peças e uma **pilha de reserva**
    com capacidade para 3 peças.\
-   Permitir as ações:
    -   **Jogar peça:** remove a peça da frente da fila.\
    -   **Reservar peça:** move a peça da frente da fila para o topo da
        pilha.\
    -   **Usar peça reservada:** remove a peça do topo da pilha.\
    -   **Exibir estado:** mostra a fila e a pilha após cada ação.\
-   Uma nova peça é gerada automaticamente após cada remoção, mantendo a
    fila sempre cheia.

#### Estruturas Utilizadas

``` c
typedef struct {
    Peca itens[MAX]; 
    int inicio, fim, total;
} Fila;

typedef struct {
    Peca itens[MAXP]; 
    int topo;
} Pilha;
```

#### Conceitos Trabalhados

-   Integração entre **fila** e **pilha**
-   **Lógica LIFO e FIFO**
-   **Reaproveitamento de espaço (fila circular)**
-   Modularização com funções específicas para cada operação

------------------------------------------------------------------------

### 🧙‍♂️ Nível Mestre

O nível final introduz **operações estratégicas avançadas**, permitindo
**trocas diretas** e **trocas múltiplas** entre a fila e a pilha.

#### Funcionalidades

-   Manter:
    -   Fila circular de 5 peças
    -   Pilha de reserva de 3 peças
-   Permitir as ações:
    -   **Jogar peça** -- remove da fila e gera nova.\
    -   **Reservar peça** -- envia da fila para o topo da pilha.\
    -   **Usar peça reservada** -- remove do topo da pilha.\
    -   **Trocar peça atual** -- troca o início da fila com o topo da
        pilha.\
    -   **Troca múltipla** -- alterna as 3 primeiras da fila com as 3 da
        pilha.\
    -   **Exibir estado atual** -- mostra fila e pilha atualizadas.\
-   Gerar novas peças automaticamente a cada remoção, mantendo o fluxo
    contínuo do jogo.

#### Exemplo de Saída

    Fila de Peças: [I 0] [L 1] [T 2] [O 3] [I 4]
    Pilha de Reserva (Topo -> Base): [O 8] [L 7] [T 6]

    Ação: troca múltipla realizada!

    Novo estado:
    Fila de Peças: [O 8] [L 7] [T 6] [O 3] [I 4]
    Pilha de Reserva (Topo -> Base): [T 2] [L 1] [I 0]

#### Conceitos Avançados

-   **Troca entre estruturas compostas**
-   **Fila circular e pilha linear**
-   **Controle de fluxo e validação de operações**
-   **Gerenciamento automático de dados**
-   **Modularização e reutilização de código**

------------------------------------------------------------------------

## 🛠️ Tecnologias Utilizadas

-   **Linguagem:** C\
-   **Compilador:** gcc\
-   **Bibliotecas:** `stdio.h`, `stdlib.h`, `string.h`, `time.h`\
-   **Execução:** Terminal / Console

------------------------------------------------------------------------

## ▶️ Como Executar

1.  Compile o código-fonte:

    ``` bash
    gcc "Tetris Stack - Mestre.c" -o tetris
    ```

2.  Execute o programa:

    ``` bash
    ./tetris
    ```

3.  Use o menu interativo para jogar, reservar e trocar peças.

------------------------------------------------------------------------

## 🧠 Conceitos Fundamentais

-   Estruturas de dados (filas e pilhas)
-   Alocação e controle de memória em C
-   Modularização e funções
-   Estruturas de repetição e decisão
-   Simulação de sistemas com lógica FIFO e LIFO

------------------------------------------------------------------------

## 🎓 Sobre o Projeto

Desenvolvido por **João Pedro Aragão dos Santos** como parte da
disciplina de **Estrutura de Dados** na **Estácio**.\
O projeto busca unir o aprendizado de **estruturas de dados** com a
**lógica de jogos**, oferecendo um ambiente lúdico para praticar
programação.

------------------------------------------------------------------------

## 📘 Licença

Projeto acadêmico sem fins comerciais. Uso permitido apenas para fins
educacionais.
