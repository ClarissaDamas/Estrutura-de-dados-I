/* arquivo: conjunto.h */

#ifndef CONJUNTO_H
#define CONJUNTO_H

/* a) Definição do tipo exportado (escondemos o que tem dentro dele) */
typedef struct conjunto Conjunto;

/* b) Funções exportadas (Ações permitidas) */
Conjunto* conjunto_cria_vazio(void);
int conjunto_insere(Conjunto* c, int elemento);
int conjunto_remove(Conjunto* c, int elemento);
Conjunto* conjunto_uniao(Conjunto* c1, Conjunto* c2);
Conjunto* conjunto_intersecao(Conjunto* c1, Conjunto* c2);
Conjunto* conjunto_diferenca(Conjunto* c1, Conjunto* c2);
int conjunto_pertence(Conjunto* c, int elemento);
int conjunto_menor_valor(Conjunto* c);
int conjunto_maior_valor(Conjunto* c);
int conjunto_sao_iguais(Conjunto* c1, Conjunto* c2);
void conjunto_destroi(Conjunto* c);

#endif
