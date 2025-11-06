# 🎒 Sistema de Mochila de Loot em C

Este projeto é uma implementação progressiva de um **sistema de
inventário (mochila virtual)**, desenvolvido em **linguagem C**, como
parte de um **trabalho acadêmico** da disciplina de **Estrutura de Dados** na **Estácio**.\
O sistema simula a coleta, organização e gerenciamento de recursos
essenciais dentro de uma mochila de jogo, utilizando **structs**,
**vetores**, **listas encadeadas** e **algoritmos de ordenação e
busca**.

## 📌 Objetivos por Nível

### 🧩 Nível Novato

O jogador deve montar sua mochila inicial coletando rapidamente **armas,
munições, kits médicos e ferramentas**.\
Neste nível, o foco está na manipulação de **structs** e **listas
sequenciais**.

#### Funcionalidades

-   Criar uma `struct Item` com os campos:

    ``` c
    char nome[30];
    char tipo[20];
    int quantidade;
    ```

-   Cadastrar até **10 itens** com nome, tipo e quantidade.

-   Remover itens informando o nome.

-   Listar todos os itens após cada operação.

-   Implementar uma **busca sequencial** para localizar itens pelo nome.

#### Requisitos Técnicos

-   Bibliotecas: `stdio.h`, `string.h`, `stdlib.h`
-   Funções obrigatórias:
    -   `inserirItem()`
    -   `removerItem()`
    -   `listarItens()`
    -   `buscarItem()`
-   Uso de `scanf()` e `fgets()` para leitura de dados.
-   Laços `for` ou `while` para percorrer o vetor de itens.

------------------------------------------------------------------------

### ⚙️ Nível Aventureiro

O jogador agora deve comparar duas formas de armazenar e acessar os
dados da mochila --- **vetores (listas sequenciais)** e **listas
encadeadas** --- para entender o impacto das estruturas na performance.

#### Funcionalidades

-   Criar duas structs:

    ``` c
    typedef struct {
        char nome[30];
        char tipo[20];
        int quantidade;
    } Item;

    typedef struct No {
        Item dados;
        struct No* proximo;
    } No;
    ```

-   Implementar **duas versões** do sistema de mochila:

    -   **Versão com vetor**
    -   **Versão com lista encadeada**

-   Operações obrigatórias em ambas:

    -   Inserir novo item
    -   Remover item por nome
    -   Listar todos os itens
    -   Buscar item por nome (busca sequencial)

-   Ordenar os itens do vetor (Bubble Sort ou Selection Sort)

-   Implementar **busca binária** após ordenação

-   Exibir **número de comparações** realizadas em cada tipo de busca

#### Requisitos Técnicos

-   Bibliotecas: `stdio.h`, `stdlib.h`, `string.h`, `time.h`
-   Modularização recomendada:
    -   `inserirItemVetor()`, `removerItemVetor()`, `ordenarVetor()`,
        `buscarSequencialVetor()`, `buscarBinariaVetor()`
    -   e equivalentes para a lista encadeada
-   Medir número de comparações e tempo de execução

------------------------------------------------------------------------

### 🧙‍♂️ Nível Mestre

A última etapa representa o **momento decisivo do jogo**, onde o jogador
precisa montar um **plano de fuga** construindo uma torre de resgate com
componentes prioritários.\
O desafio final consiste em aplicar **algoritmos de ordenação e busca
binária** e analisar seu desempenho.

#### Funcionalidades

-   Criar a struct:

    ``` c
    typedef struct {
        char nome[30];
        char tipo[20];
        int prioridade;
    } Componente;
    ```

-   Cadastrar até **20 componentes** com nome, tipo e prioridade (1 a
    10)

-   Implementar diferentes algoritmos de ordenação:

    -   **Bubble Sort** → Ordenar por nome
    -   **Insertion Sort** → Ordenar por tipo
    -   **Selection Sort** → Ordenar por prioridade

-   Aplicar **busca binária** após ordenação por nome

-   Exibir:

    -   Número de comparações
    -   Tempo de execução (`clock()`)

-   Mostrar os componentes ordenados e destacar o componente-chave

#### Requisitos Técnicos

-   Bibliotecas: `stdio.h`, `stdlib.h`, `string.h`, `time.h`
-   Funções obrigatórias:
    -   `bubbleSortNome()`
    -   `insertionSortTipo()`
    -   `selectionSortPrioridade()`
    -   `buscaBinariaPorNome()`
    -   `mostrarComponentes()`
    -   `medirTempo()`

------------------------------------------------------------------------

## 🛠️ Tecnologias Utilizadas

-   **Linguagem:** C\
-   **Compilador:** gcc\
-   **Execução:** Terminal / Console

## ▶️ Como Executar

1.  Compile o código-fonte:

    ``` bash
    gcc "Free Fire Inventário - Mestre (Lista Sequencial).c" -o mochila
    ```

2.  Execute o programa:

    ``` bash
    ./mochila
    ```

3.  Interaja com o menu para:

    -   Adicionar, remover e listar componentes
    -   Organizar a mochila por diferentes critérios
    -   Realizar buscas e analisar desempenho

------------------------------------------------------------------------

## 🧠 Conceitos Trabalhados

-   Estruturas de dados compostas (`struct`)
-   Vetores e listas encadeadas
-   Ordenação (Bubble, Insertion, Selection)
-   Busca sequencial e binária
-   Modularização e funções
-   Medição de tempo e contagem de comparações
-   Boas práticas de programação e documentação

------------------------------------------------------------------------

## 🎓 Sobre o Projeto

Projeto desenvolvido por **João Pedro Aragão dos Santos** como parte da
disciplina de **Estrutura de Dados** na **Estácio**.\
Tem como objetivo integrar os principais conceitos de **estrutura de
dados**, **ordenamento** e **busca eficiente** em um cenário de jogo.

------------------------------------------------------------------------

## 📘 Licença

Projeto acadêmico sem fins comerciais. Uso exclusivo para fins
educacionais.
