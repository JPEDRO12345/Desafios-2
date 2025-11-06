#include <stdio.h>
#include "inventario.h"

// Função Principal
// Se tiver C instaldo no pc, abra o Terminal na pasta onde estão os arquivos e use isso no terminal para compilar: gcc main.c inventario.c utils.c -o inventario.exe
int main(){
    item mochila[MAX_LISTA]; // Array que armazena as informações dos itens
    int opcao;
    int contador = 0; // Contador para gerenciar a adicição de itens

    do
    {
        printf("\n-----------Inventário-----------\n");
        printf("O que deseja fazer?\n");
        printf("1-Adicionar Componente\n2-Descartar Componente\n3-Listar Componentes\n4-Organizar Mochila\n5-Busca Binária (faz ordenação automaticamente)\n0-Sair\n");
        printf("Digite aqui: ");
        scanf("%d", &opcao);
        Limpador_De_Buffer();

        switch (opcao)
        {
        case 1:
            Cadastro_Item(mochila, &contador); // Função responsavel pelo Cadastro de itens
            break;
        
        case 2:
            Remover_Item(mochila, &contador);
            break;
        case 3:
            Apresentacao_Itens(mochila, contador);
            break;
        
        case 4:
        {   int escolha_ordem;
            do
            {
            printf("\nQual Tipo de Ordenação deseja fazer?\n1-Ordem Alfabética\n2-Ordem de Prioridade\n3-Ordem por tipo\n");
            printf("Digite aqui: ");
            scanf("%d", &escolha_ordem);
            Limpador_De_Buffer();

            // Switch com os tipos de ordenação
            switch (escolha_ordem)
            {
            case 1:
                Ordem_Alfabetica(mochila, contador);
                Apresentacao_Itens(mochila, contador);
                break;
            
            case 2:
                Ordenar_Prioridade(mochila, contador);
                Apresentacao_Itens(mochila, contador);
                break;
            
            case 3:
                Ordenar_Tipo(mochila, contador);
                Apresentacao_Itens(mochila, contador);
                break;
            
            case 0:
                break;
                break;
            default:
                printf("\nDigite um Valor válido!\n");
                break;
            }
            } while (escolha_ordem < 1 || escolha_ordem > 3);;

            break;
        }
        case 5:
            Buscar_Item_Binario(mochila, contador);
            break;
        
        case 0:
        printf("\nSaindo do programa: Pressione Enter\n");
        break;
        break;
        
        default:
            printf("\nErro! Digite um valor válido\n");
            break;
        }
    if (opcao !=0 && opcao != 4) // Só executa se o valor escolhido for diferente de 0 e de 4
    {
        // Chamada da função responsável pela apresentação dos itens cadastrados
        Apresentacao_Itens(mochila, contador);
    }
    } while (opcao != 0);
}
