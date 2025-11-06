#include <stdio.h>
#include <string.h>


// Função que Limpa o buffer para evitar problemas ao usar fgets
void Limpador_De_Buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Para Remover o '\n' automatico do fgets
void Remove_n(char *str) {
    str[strcspn(str, "\n")] = '\0'; // Remove o '\n' se houver
}
