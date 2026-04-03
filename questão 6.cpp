#include <stdio.h>
#include <string.h>

// Função recursiva
void buscaSubstring(char str[], char sub[], int i) {
    int tamStr = strlen(str);
    int tamSub = strlen(sub);

    // Caso base: se não há mais espaço para comparar
    if (i > tamStr - tamSub) {
        return;
    }

    // Verifica se a substring começa na posição i
    int j;
    for (j = 0; j < tamSub; j++) {
        if (str[i + j] != sub[j]) {
            break;
        }
    }

    // Se percorreu toda a substring, encontrou ocorrência
    if (j == tamSub) {
        printf("Substring encontrada na posicao %d\n", i);
    }

    // Chamada recursiva para próxima posição
    buscaSubstring(str, sub, i + 1);
}

// Função principal
int main() {
    char str[100], sub[100];

    printf("Digite a string principal: ");
    fgets(str, 100, stdin);
    str[strcspn(str, "\n")] = '\0'; // remove o '\n'

    printf("Digite a substring: ");
    fgets(sub, 100, stdin);
    sub[strcspn(sub, "\n")] = '\0';

    buscaSubstring(str, sub, 0);

    return 0;
}
