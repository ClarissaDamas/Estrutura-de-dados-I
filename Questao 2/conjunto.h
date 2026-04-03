#ifndef CONJUNTO_H
#define CONJUNTO_H

#define MAX 100

typedef struct {
    int elementos[MAX];
    int tamanho;
} Conjunto;

Conjunto* criar();
void destruir(Conjunto* c);
int inserir(Conjunto* c, int valor);
int remover(Conjunto* c, int valor);
int pertence(Conjunto* c, int valor);
Conjunto* uniao(Conjunto* a, Conjunto* b);
Conjunto* intersecao(Conjunto* a, Conjunto* b);
Conjunto* diferenca(Conjunto* a, Conjunto* b);
int menor(Conjunto* c);
int maior(Conjunto* c);
int iguais(Conjunto* a, Conjunto* b);
void imprimir(Conjunto* c);

#endif
