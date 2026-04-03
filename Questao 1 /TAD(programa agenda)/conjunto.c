/* arquivo: conjunto.c */

#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"

/* a) Definição da estrutura para armazenar os dados */
struct conjunto {
    int *elementos;   // Vetor dinâmico para guardar os inteiros
    int tamanho;      // Quantidade atual de elementos no conjunto
    int capacidade;   // Capacidade máxima atual do vetor
};

/* Criando um conjunto vazio */
Conjunto* conjunto_cria_vazio(void) {
    Conjunto* c = (Conjunto*) malloc(sizeof(Conjunto));
    if (c == NULL) {
        printf("Memória insuficiente!\n");
        exit(1);
    }
    c->tamanho = 0;
    c->capacidade = 10; // Começamos com espaço para 10 elementos, por exemplo
    c->elementos = (int*) malloc(c->capacidade * sizeof(int));
    
    return c;
}
