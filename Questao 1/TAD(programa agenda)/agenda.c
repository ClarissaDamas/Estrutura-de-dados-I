

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

/* ----------------------------------------------------------
   Funcoes PRIVADAS (static = visivel apenas neste arquivo)
   ---------------------------------------------------------- */

/* Realoca o vetor para (novoTotal) elementos.
   Retorna 1 se ok, 0 se falha. */
static int realocar(Agenda *ag, int novoTotal)
{
    Contato *tmp = (Contato *)realloc(ag->vetor,
                                      novoTotal * sizeof(Contato));
    if (tmp == NULL && novoTotal > 0)
        return 0;          /* falha: ag->vetor continua valido */
    ag->vetor = tmp;
    return 1;
}

/* Busca linear pelo nome (prefixo exato, case-sensitive).
   Retorna indice do primeiro encontrado ou -1. */
static int buscar(const Agenda *ag, const char *nome)
{
    int i;
    size_t len = strlen(nome);
    for (i = 0; i < ag->total; i++)
        if (strncmp(ag->vetor[i].nome, nome, len) == 0)
            return i;
    return -1;
}

/* Quicksort interno por nome */
static void qs_ordena(Contato v[], int left, int right)
{
    int i = left, j = right;
    char *pivo = v[(left + right) / 2].nome;
    Contato tmp;

    do {
        while (strcmp(v[i].nome, pivo) < 0 && i < right) i++;
        while (strcmp(v[j].nome, pivo) > 0 && j > left ) j--;
        if (i <= j) {
            tmp  = v[i];
            v[i] = v[j];
            v[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);

    if (left  < j) qs_ordena(v, left, j);
    if (i < right) qs_ordena(v, i, right);
}

/* ----------------------------------------------------------
   Implementacao das operacoes PUBLICAS
   ---------------------------------------------------------- */

void Agenda_inicializar(Agenda *ag)
{
    ag->vetor = NULL;
    ag->total = 0;
}

void Agenda_destruir(Agenda *ag)
{
    free(ag->vetor);
    ag->vetor = NULL;
    ag->total = 0;
}

int Agenda_incluir(Agenda *ag, const char *nome,
                   const char *email, int telefone)
{
    /* tenta ampliar o vetor em 1 posicao */
    if (!realocar(ag, ag->total + 1))
    {
        fprintf(stderr, "\nErro: falha ao alocar memoria.\n");
        return 0;
    }

    /* preenche o novo elemento */
    strncpy(ag->vetor[ag->total].nome,  nome,  39);
    strncpy(ag->vetor[ag->total].email, email, 39);
    ag->vetor[ag->total].nome [39] = '\0';
    ag->vetor[ag->total].email[39] = '\0';
    ag->vetor[ag->total].telefone  = telefone;

    ag->total++;
    return 1;
}

int Agenda_excluir(Agenda *ag, const char *nome)
{
    int idx = buscar(ag, nome);
    if (idx < 0)
        return 0;   /* nao encontrado */

    /* substitui pelo ultimo e encolhe o vetor */
    ag->vetor[idx] = ag->vetor[ag->total - 1];
    ag->total--;

    /* realloc para liberar a posicao extra (falha aqui nao e critica) */
    realocar(ag, ag->total > 0 ? ag->total : 1);
    return 1;
}

int Agenda_alterar(Agenda *ag, const char *nome,
                   const char *novoNome, const char *novoEmail,
                   int novoTelefone)
{
    int idx = buscar(ag, nome);
    if (idx < 0)
        return 0;

    strncpy(ag->vetor[idx].nome,  novoNome,  39);
    strncpy(ag->vetor[idx].email, novoEmail, 39);
    ag->vetor[idx].nome [39] = '\0';
    ag->vetor[idx].email[39] = '\0';
    ag->vetor[idx].telefone  = novoTelefone;
    return 1;
}

void Agenda_ordenar(Agenda *ag)
{
    if (ag->total > 1)
        qs_ordena(ag->vetor, 0, ag->total - 1);
}

void Agenda_consultar(Agenda *ag)
{
    int i;
    if (ag->total == 0)
    {
        printf("\n\tNenhum contato cadastrado.\n");
        return;
    }
    Agenda_ordenar(ag);
    for (i = 0; i < ag->total; i++)
    {
        printf("\n\n  Registro %d", i + 1);
        printf("\n\tNome     : %s", ag->vetor[i].nome    );
        printf("\n\tEmail    : %s", ag->vetor[i].email   );
        printf("\n\tTelefone : %d", ag->vetor[i].telefone);
    }
    printf("\n");
}

void Agenda_pesquisar(Agenda *ag, const char *prefixo)
{
    int i;
    int achou = 0;

    if (ag->total == 0)
    {
        printf("\n\tNenhum contato cadastrado.\n");
        return;
    }
    Agenda_ordenar(ag);

    printf("\n--- Resultados para \"%s\" ---", prefixo);
    for (i = 0; i < ag->total; i++)
    {
        if (strncmp(ag->vetor[i].nome, prefixo, strlen(prefixo)) == 0)
        {
            printf("\n\n  Registro %d", i + 1);
            printf("\n\tNome     : %s", ag->vetor[i].nome    );
            printf("\n\tEmail    : %s", ag->vetor[i].email   );
            printf("\n\tTelefone : %d", ag->vetor[i].telefone);
            achou = 1;
        }
    }
    if (!achou)
        printf("\n\tNenhum registro encontrado.\n");
    else
        printf("\n");
}

int Agenda_total(const Agenda *ag)
{
    return ag->total;
}
