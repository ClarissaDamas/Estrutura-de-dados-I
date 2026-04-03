#ifndef AGENDA_H
#define AGENDA_H

typedef struct {
    char nome[40];
    char email[40];
    int  telefone;
} Contato;

typedef struct {
    Contato *vetor;    /* vetor dinamico de contatos        */
    int      total;    /* quantidade de contatos cadastrados */
} Agenda;

void Agenda_inicializar(Agenda *ag);
/* Libera toda a memoria alocada pela agenda */
void Agenda_destruir(Agenda *ag);
/* Inclui um novo contato; retorna 1 se ok, 0 se falha de memoria */
int  Agenda_incluir(Agenda *ag, const char *nome,
                    const char *email, int telefone);
int  Agenda_excluir(Agenda *ag, const char *nome);

/* Altera os dados do contato com o nome informado; retorna 1 se encontrado */
int  Agenda_alterar(Agenda *ag, const char *nome,
                    const char *novoNome, const char *novoEmail,
                    int novoTelefone);

/* Consulta (imprime) todos os contatos em ordem alfabetica */
void Agenda_consultar(Agenda *ag);

/* Pesquisa contatos cujo nome comeca com o prefixo informado */
void Agenda_pesquisar(Agenda *ag, const char *prefixo);

/* Ordena o vetor interno por nome (quicksort) */
void Agenda_ordenar(Agenda *ag);

/* Retorna o total de contatos cadastrados */
int  Agenda_total(const Agenda *ag);
#endif
