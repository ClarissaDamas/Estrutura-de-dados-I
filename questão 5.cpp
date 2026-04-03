#include <stdio.h>
#include <string.h>

// Função recursiva para imprimir a string invertida
void imprimeInvertido(char str[], int i) {
    // Caso base: fim da string
    if (str[i] == '\0') {
        return;
    }

    // Chamada recursiva
    imprimeInvertido(str, i + 1);

    // Impressão após a recursão
    printf("%c", str[i]);
}

int main() {
    char str[100];

    printf("Digite uma string: ");
    fgets(str, 100, stdin);

    // Remove o '\n' do fgets (opcional, mas melhor)
    str[strcspn(str, "\n")] = '\0';

    printf("String invertida: ");
    imprimeInvertido(str, 0);

    printf("\n");

    return 0;
}
