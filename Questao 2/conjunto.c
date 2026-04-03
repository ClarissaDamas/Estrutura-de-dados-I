#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"

Conjunto* criar() {
    Conjunto* c = (Conjunto*) malloc(sizeof(Conjunto));
    c->tamanho = 0;
    return c;
}

void destruir(Conjunto* c) {
    free(c);
}

int pertence(Conjunto* c, int valor) {
    for (int i = 0; i < c->tamanho; i++)
        if (c->elementos[i] == valor) return 1;
    return 0;
}

int inserir(Conjunto* c, int valor) {
    if (c->tamanho >= MAX || pertence(c, valor)) return 0;
    c->elementos[c->tamanho++] = valor;
    return 1;
}

int remover(Conjunto* c, int valor) {
    for (int i = 0; i < c->tamanho; i++) {
        if (c->elementos[i] == valor) {
            c->elementos[i] = c->elementos[--c->tamanho];
            return 1;
        }
    }
    return 0;
}

Conjunto* uniao(Conjunto* a, Conjunto* b) {
    Conjunto* r = criar();
    for (int i = 0; i < a->tamanho; i++) inserir(r, a->elementos[i]);
    for (int i = 0; i < b->tamanho; i++) inserir(r, b->elementos[i]);
    return r;
}

Conjunto* intersecao(Conjunto* a, Conjunto* b) {
    Conjunto* r = criar();
    for (int i = 0; i < a->tamanho; i++)
        if (pertence(b, a->elementos[i])) inserir(r, a->elementos[i]);
    return r;
}

Conjunto* diferenca(Conjunto* a, Conjunto* b) {
    Conjunto* r = criar();
    for (int i = 0; i < a->tamanho; i++)
        if (!pertence(b, a->elementos[i])) inserir(r, a->elementos[i]);
    return r;
}

int menor(Conjunto* c) {
    if (c->tamanho == 0) return -1;
    int m = c->elementos[0];
    for (int i = 1; i < c->tamanho; i++)
        if (c->elementos[i] < m) m = c->elementos[i];
    return m;
}

int maior(Conjunto* c) {
    if (c->tamanho == 0) return -1;
    int m = c->elementos[0];
    for (int i = 1; i < c->tamanho; i++)
        if (c->elementos[i] > m) m = c->elementos[i];
    return m;
}

int iguais(Conjunto* a, Conjunto* b) {
    if (a->tamanho != b->tamanho) return 0;
    for (int i = 0; i < a->tamanho; i++)
        if (!pertence(b, a->elementos[i])) return 0;
    return 1;
}

void imprimir(Conjunto* c) {
    printf("{ ");
    for (int i = 0; i < c->tamanho; i++)
        printf("%d ", c->elementos[i]);
    printf("}\n");
}
