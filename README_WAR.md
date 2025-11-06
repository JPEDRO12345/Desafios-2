# 🎲 WAR -- Simulação Estratégica em C

Este projeto é uma implementação progressiva inspirada no clássico jogo
**WAR**, desenvolvida em linguagem **C**, como trabalho acadêmico para a
disciplina de **Estrutura de Dados** na **Estácio**. O
desenvolvimento é dividido em três níveis de desafio: **Novato**,
**Aventureiro** e **Mestre**, abordando estruturas, ponteiros, alocação
dinâmica de memória e modularização.

## 📌 Objetivos por Nível

### 🧩 Nível Novato

-   Criar uma `struct Territorio` com os campos:
    -   `char nome[30]`
    -   `char cor[10]`
    -   `int tropas`
-   Cadastrar **5 territórios**, informando nome, cor do exército e
    quantidade de tropas.
-   Exibir os dados cadastrados de forma formatada no console.

### ⚔️ Nível Aventureiro

-   Utilizar **alocação dinâmica** (`malloc` ou `calloc`) para criar o
    vetor de territórios.

-   Implementar a função:

    ``` c
    void atacar(Territorio* atacante, Territorio* defensor);
    ```

    que simula uma batalha usando números aleatórios de 1 a 6.

-   Atualizar automaticamente os dados dos territórios:

    -   O vencedor assume o território e transfere metade das tropas.
    -   O perdedor perde uma tropa.

-   Exibir os territórios atualizados após cada ataque.

-   Liberar toda a memória alocada ao final da execução.

### 🧙‍♂️ Nível Mestre

-   Criar e gerenciar **missões estratégicas** para cada jogador.

-   Armazenar as missões em um vetor de strings, sorteadas
    aleatoriamente no início do jogo.

-   Exemplos de missões:

    -   *"Conquistar 1 território inimigo"*
    -   *"Eliminar todas as tropas da cor X"*
    -   *"Sobreviver com pelo menos 3 territórios ativos"*
    -   *"Reduzir as tropas inimigas de um território a zero"*
    -   *"Seu território ter pelo menos 3 tropas"*

-   Implementar as funções:

    ``` c
    void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
    int verificarMissao(char* missao, Territorio* mapa, int tamanho);
    ```

-   Verificar automaticamente se algum jogador cumpriu sua missão ao
    final de cada turno e declarar o vencedor.

-   Garantir o uso correto de **ponteiros**, **passagem por valor e
    referência**, e **liberação da memória**.

## 🛠️ Tecnologias Utilizadas

-   Linguagem: **C**
-   Bibliotecas: `stdio.h`, `stdlib.h`, `string.h`, `time.h`
-   Compilador sugerido: **gcc**
-   Execução via terminal

## ▶️ Como Executar

1.  Compile o código-fonte:

    ``` bash
    gcc "War - Mestre.c" -o war
    ```

2.  Execute o programa:

    ``` bash
    ./war
    ```

3.  Siga as instruções no terminal para cadastrar territórios, realizar
    ataques e completar missões.

## 📷 Exemplo de Execução

    =============================================
    TERRITÓRIOS DO MAPA
    =============================================
    1. Brasil (Exército Azul, Tropas: 5)
    2. Argentina (Exército Vermelho, Tropas: 4)
    3. Chile (Exército Verde, Tropas: 3)

    Missão atribuída: Conquistar 1 território inimigo
    Status da Missão: ❌ INCOMPLETA

## 🧠 Conceitos Envolvidos

-   Estruturas (`struct`)
-   Vetores de estruturas
-   Ponteiros e passagem por referência
-   Alocação e liberação dinâmica de memória (`malloc`, `calloc`,
    `free`)
-   Geração de números aleatórios (`rand()` e `srand()`)
-   Modularização e boas práticas de programação
-   Lógica de combate e verificação de vitória

## 🎓 Sobre o Projeto

Projeto desenvolvido por **João Pedro Aragão dos Santos** como parte da
disciplina de **Estrutura de Dados** na **Estácio**.\
Tem como objetivo exercitar o uso de estruturas, ponteiros e manipulação
dinâmica de dados em linguagem C.

## 📘 Licença

Projeto acadêmico sem fins comerciais. Uso permitido apenas para fins
educacionais.