#include <stdio.h>
#include "conjunto.h"

int main() {
    Conjunto* a = criar();
    Conjunto* b = criar();

    inserir(a, 1); inserir(a, 2); inserir(a, 3); inserir(a, 4);
    inserir(b, 3); inserir(b, 4); inserir(b, 5); inserir(b, 6);

    printf("A = "); imprimir(a);
    printf("B = "); imprimir(b);

    Conjunto* u = uniao(a, b);
    printf("Uniao       = "); imprimir(u);

    Conjunto* inter = intersecao(a, b);
    printf("Intersecao  = "); imprimir(inter);

    Conjunto* dif = diferenca(a, b);
    printf("Diferenca   = "); imprimir(dif);

    printf("3 pertence a A? %s\n", pertence(a, 3) ? "Sim" : "Nao");
    printf("7 pertence a A? %s\n", pertence(a, 7) ? "Sim" : "Nao");
    printf("Menor de A: %d\n", menor(a));
    printf("Maior de A: %d\n", maior(a));
    printf("A == B? %s\n", iguais(a, b) ? "Sim" : "Nao");
    printf("A == A? %s\n", iguais(a, a) ? "Sim" : "Nao");

    remover(a, 2);
    printf("A apos remover 2: "); imprimir(a);

    destruir(a); destruir(b);
    destruir(u); destruir(inter); destruir(dif);

    return 0;
}
