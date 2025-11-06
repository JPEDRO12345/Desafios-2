# 🕵️‍♂️ Detective Quest em C

Este projeto é uma implementação progressiva do jogo educativo **Detective Quest**, desenvolvido em linguagem **C**, como trabalho acadêmico para a disciplina de **Estrutura de Dados** na **Estácio**.  
O jogo foi criado pela fictícia **Enigma Studios**, e desafia o jogador a explorar uma mansão misteriosa, coletar pistas e descobrir o verdadeiro culpado.

O desenvolvimento é dividido em três níveis de desafio: **Novato**, **Aventureiro** e **Mestre**, cada um introduzindo novos conceitos e estruturas de dados da linguagem C.

---

## 📌 Objetivos por Nível

### 🧩 Nível Novato
- Criar um **mapa da mansão** representado por uma **árvore binária**.
- Permitir ao jogador **explorar os cômodos** a partir do "Hall de Entrada".
- Em cada cômodo, o jogador escolhe ir para a esquerda (`e`), direita (`d`) ou sair (`s`).
- Exibir o nome de cada sala visitada até alcançar um **nó-folha** (sem caminhos disponíveis).

**Conceitos trabalhados:**
- Árvores binárias.
- Alocação dinâmica com `malloc`.
- Estruturas (`structs`) para representar os cômodos.
- Uso de condicionais (`if`, `else`).
- Modularização com funções dedicadas (`criarSala`, `explorarSalas`, `main`).

---

### 🔍 Nível Aventureiro
- Adicionar **pistas** associadas a cada cômodo da mansão.
- Criar uma **árvore BST (Binary Search Tree)** para armazenar as pistas coletadas.
- Inserir automaticamente cada pista encontrada na BST.
- Exibir todas as pistas **em ordem alfabética** ao final da exploração.

**Conceitos trabalhados:**
- Árvores binárias de busca (BST).
- Recursividade para percorrer e exibir pistas.
- Alocação dinâmica e modularização.
- Separação clara entre o mapa da mansão e o sistema de pistas.

---

### 💼 Nível Mestre
- Permitir **exploração interativa** da mansão binária.
- Associar cada pista a um suspeito através de uma **tabela hash**.
- Inserir as associações pista → suspeito na tabela.
- Contabilizar as pistas que apontam para o suspeito acusado.
- Determinar automaticamente se há **pistas suficientes para a acusação final**.

**Conceitos trabalhados:**
- Árvores binárias e árvores de busca.
- Tabela hash com encadeamento.
- Alocação dinâmica e ponteiros.
- Recursividade e funções auxiliares.
- Lógica condicional e tomada de decisão.

---

## 🛠️ Tecnologias Utilizadas
- Linguagem: **C**
- Compilador sugerido: **gcc**
- Execução via **terminal/console**

---

## ▶️ Como Executar

1. Clone o repositório:
   ```bash
   git clone https://github.com/JPEDRO12345/DetectiveQuest.git
   ```

2. Compile o código-fonte (nível mestre):
   ```bash
   gcc "Detective Quest - Mestre.c" -o detective
   ```

3. Execute o programa:
   ```bash
   ./detective
   ```

---

## 🧠 Exemplo de Fluxo de Jogo

```
Você está no Hall de Entrada.
Você encontrou uma pista: Um bilhete rasgado com a letra A.

Para onde quer ir?
1 - Esquerda
2 - Direita
0 - Voltar

> 1
Você foi para: Sala de Estar
Você encontrou uma pista: Uma chave dourada caída no sofá.

> 0
Você está no Hall de Entrada. Encerrando exploração...
```

### Saída Final:
```
--- Sequência de Cômodos Visitados ---
1. Hall de Entrada
2. Sala de Estar

--- Pistas Coletadas ---
- Um bilhete rasgado com a letra A.
- Uma chave dourada caída no sofá.

Quem você acusa? Suspeito B
Pistas que apontam para 'Suspeito B': 2
Acusação aceita: há pistas suficientes para sustentar a acusação contra Suspeito B.
```

---

## 🎓 Sobre o Projeto
Este projeto foi desenvolvido por **João Pedro Aragão dos Santos** como parte de um **trabalho acadêmico** da disciplina de **Estrutura de Dados** na **Estácio**.  

Tem como objetivo exercitar:
- Estruturas de dados (árvore binária, BST, tabela hash).
- Lógica de decisão e recursividade.
- Modularização e documentação de código.
- Boas práticas de programação em C.

---

## 📘 Licença
Este projeto é **acadêmico e educacional**, sem fins comerciais.  
Livre para consulta e estudo.
