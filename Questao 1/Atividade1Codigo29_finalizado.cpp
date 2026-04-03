/* agenda.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Substitui getch() de conio.h/curses.h por versao portavel */
static int getch(void)
{
    int c = getchar();
    /* consome o restante da linha se necessario */
    return c;
}

typedef struct agenda
{
    char nome[40];
    char email[40];
    int  telefone;
} AGENDA;

void aloca   ( AGENDA **pAgenda, int *piEntradas );
void consulta( AGENDA  *pAgenda, int  iEntradas );

void qs_ordena(AGENDA pAgenda[], int left, int right );
void ordena   ( AGENDA pAgenda[], int iEntradas );

void excluir  (AGENDA **pAgenda, int *piEntradas);
void pesquisar(AGENDA  *pAgenda, int  iEntradas);
void alterar  (AGENDA  *pAgenda, int  iEntradas);

/* ---------- main ---------- */
int main(void)
{
    AGENDA *pAgenda;

    int iEntradas, op;
    iEntradas = 0;

    pAgenda = (AGENDA *) malloc(sizeof(AGENDA)); /* aloca espaco para a posicao 0 */
    if( pAgenda == NULL )
    {
        printf("\nErro de alocacao de memoria.");
        exit(1);
    }

    do
    {
        fflush(stdin);
        printf("\n1 - Inclusao");
        printf("\n2 - Alteracao");
        printf("\n3 - Consulta");
        printf("\n4 - Excluir");
        printf("\n5 - Pesquisar");
        printf("\n9 - Sair");
        printf("\nEntre com uma opcao -> ");
        scanf("%d", &op);

        if( op == 1 )
        {
            fflush(stdin);

            aloca(&pAgenda, &iEntradas);

            printf("*** Inclusao ***");
            printf("\nEntre com o Nome:");
            /* fgets substitui gets() (obsoleto/removido do C11) */
            fgets((pAgenda+iEntradas)->nome,  40, stdin);
            /* remove '\n' deixado pelo fgets */
            (pAgenda+iEntradas)->nome[strcspn((pAgenda+iEntradas)->nome, "\n")] = '\0';
            fflush(stdin);

            printf("Entre com o email:");
            fgets((*(pAgenda+iEntradas)).email, 40, stdin);
            (*(pAgenda+iEntradas)).email[strcspn((*(pAgenda+iEntradas)).email, "\n")] = '\0';
            fflush(stdin);

            printf("Entre com o telefone:");
            scanf("%d", &pAgenda[iEntradas].telefone);
            fflush(stdin);

            iEntradas++;
        }
        else if( op == 2 )
        {
            alterar(pAgenda, iEntradas);
        }
        else if( op == 3 )
        {
            ordena(pAgenda, iEntradas);
            consulta(pAgenda, iEntradas);
        }
        else if( op == 4 )
        {
            ordena(pAgenda, iEntradas);
            excluir(&pAgenda, &iEntradas);
        }
        else if( op == 5 )
        {
            ordena(pAgenda, iEntradas);
            pesquisar(pAgenda, iEntradas);
        }
    } while(op!=9);

    free(pAgenda);
    return 0;
}

/* ---------- consulta ---------- */
void consulta(AGENDA *pAgenda, int iEntradas)
{
    int i;
    for(i=0; i<iEntradas; i++)
    {
        printf("\n\nRegistro %d", i);
        printf("\n\tNome     : %s", pAgenda[i].nome     );
        printf("\n\tEmails   : %s", pAgenda[i].email    );
        printf("\n\tTelefone : %d", pAgenda[i].telefone );
        getch();
    }
}

/* ---------- alterar ---------- */
void alterar(AGENDA *pAgenda, int iEntradas)
{
    char op;
    int  i=0;
    char nome[40];
    printf("\n\tDigite o Nome:");
    fflush(stdin);
    fgets(nome, 40, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for(i=0; i < iEntradas && strncmp( pAgenda[i].nome, nome, strlen(nome))!=0; i++);
    if( i>= iEntradas )
    {
        printf("\nRegistro nao encontrado");
    }
    else
    {
        printf("\n\tRegistro %d", i);
        printf("\n\tNome  : %s", pAgenda[i].nome    );
        printf("\n\tEmail : %s", pAgenda[i].email   );
        printf("\n\tFone  : %d", pAgenda[i].telefone);
        printf("\n\tConfirma a alteracao ?");
        op = getch();
        if( op == 'S' || op == 's' )
        {
            fflush(stdin);
            printf("\nEntre com o Nome:");
            fgets((pAgenda+i)->nome, 40, stdin);
            (pAgenda+i)->nome[strcspn((pAgenda+i)->nome, "\n")] = '\0';
            fflush(stdin);

            printf("Entre com o email:");
            fgets((*(pAgenda+i)).email, 40, stdin);
            (*(pAgenda+i)).email[strcspn((*(pAgenda+i)).email, "\n")] = '\0';
            fflush(stdin);

            printf("Entre com o telefone:");
            scanf("%d", &pAgenda[i].telefone);
            fflush(stdin);
        }
    }
}

/* ---------- excluir ---------- */
void excluir(AGENDA **pAgenda, int *piEntradas)
{
    char op;
    int  i=0;
    char nome[40];
    printf("\n\tDigite o Nome:");
    fflush(stdin);
    fgets(nome, 40, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for(i=0; i < *piEntradas && strncmp( (*pAgenda)[i].nome, nome, strlen(nome))!=0; i++);
    if( i>= *piEntradas )
    {
        printf("\nRegistro nao encontrado");
    }
    else
    {
        fflush(stdin);
        printf("\n\tRegistro %d", i);
        printf("\n\tNome  : %s", (*pAgenda)[i].nome    );
        printf("\n\tEmail : %s", (*pAgenda)[i].email   );
        printf("\n\tFone  : %d", (*pAgenda)[i].telefone);
        printf("\n\tConfirma a exclusao ?");
        op = getch();
        if( op == 'S' || op == 's' )
        {
            /* copia o ultimo elemento para o elemento corrente */
            (*pAgenda)[i] = (*pAgenda)[(*piEntradas)-1];
            (*piEntradas)--;
            /* exclui o ultimo elemento com realloc */
            aloca(pAgenda, piEntradas);
        }
    }
}

/* ---------- aloca ---------- */
void aloca( AGENDA **pAgenda, int *piEntradas )
{
    (*pAgenda) = (AGENDA *)(realloc(*pAgenda,
                    (*piEntradas+1)*sizeof(AGENDA)));
    if( *pAgenda == NULL )
    {
        printf("\nErro de re-alocacao de memoria");
        exit(1);
    }
}

/* ---------- pesquisar ---------- */
void pesquisar(AGENDA *pAgenda, int iEntradas)
{
    char op;
    int  i=0;
    char nome[40];
    printf("\n\tDigite o Nome:");
    fflush(stdin);
    fgets(nome, 40, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for(i=0; i < iEntradas && strncmp( pAgenda[i].nome, nome, strlen(nome))!=0; i++);
    if( i>= iEntradas )
    {
        printf("\nRegistro nao encontrado");
    }
    else
    {
        do
        {
            fflush(stdin);
            printf("\n\n\tRegistro %d", i);
            printf("\n\tNome  : %s", pAgenda[i].nome    );
            printf("\n\tEmail : %s", pAgenda[i].email   );
            printf("\n\tFone  : %d", pAgenda[i].telefone);
            printf("\n\tProximo ?");
            op = getch();
            i++;
            if(i>=iEntradas)
            {
                i = 0;
            }
        } while( op == 'S' || op == 's');
    }
}

/* ---------- ordena (wrapper) ---------- */
void ordena( AGENDA pAgenda[], int iEntradas )
{
    qs_ordena(pAgenda, 0, iEntradas-1 );
}

/* ---------- qs_ordena (quicksort por nome) ---------- */
void qs_ordena(AGENDA pAgenda[], int left, int right )
{
    register int i, j;
    /* pivot: nome do elemento central */
    char *x;          /* apenas ponteiro para comparacao */
    AGENDA t;          /* elemento temporario para troca */

    i = left;
    j = right;
    x = pAgenda[(left+right)/2].nome;

    do
    {
        while(strcmp(pAgenda[i].nome,x)<0 && i<right) i++;
        while(strcmp(pAgenda[j].nome,x)>0 && j>left ) j--;
        if( i<=j )
        {
            t           = pAgenda[i];
            pAgenda[i]  = pAgenda[j];
            pAgenda[j]  = t;
            i++;
            j--;
        }
    } while( i<=j );
    if( left  < j ) qs_ordena(pAgenda, left, j);
    if( i < right ) qs_ordena(pAgenda, i, right );
}
