#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>      /* getch() nativo do Dev C++ / MinGW */
#include "agenda.h"

/* Le uma string do teclado, remove o '\n' e limpa o buffer */
static void ler_string(const char *prompt, char *buf, int tam)
{
    printf("%s", prompt);
    fflush(stdout);
    fgets(buf, tam, stdin);
    buf[strcspn(buf, "\n")] = '\0';
}

/* Le um inteiro do teclado e limpa o buffer */
static int ler_int(const char *prompt)
{
    int v;
    printf("%s", prompt);
    scanf("%d", &v);
    /* descarta o '\n' que fica no buffer apos scanf */
    while (getchar() != '\n');
    return v;
}

/* Exibe uma mensagem e aguarda o usuario pressionar qualquer tecla */
static void pausar(const char *msg)
{
    printf("\n%s", msg);
    getch();
}

/* ----------------------------------------------------------
   Telas do menu
   ---------------------------------------------------------- */

static void tela_incluir(Agenda *ag)
{
    char nome[40], email[40];
    int  tel;

    system("cls");   /* limpa a tela no Windows / Dev C++ */
    printf("========== INCLUSAO ==========\n");
    ler_string("Nome     : ", nome,  40);
    ler_string("Email    : ", email, 40);
    tel = ler_int  ("Telefone : ");

    if (Agenda_incluir(ag, nome, email, tel))
        pausar("Contato incluido com sucesso! Pressione qualquer tecla...");
    else
        pausar("ERRO ao incluir contato. Pressione qualquer tecla...");
}

static void tela_alterar(Agenda *ag)
{
    char busca[40], nome[40], email[40];
    int  tel;
    char confirma;

    system("cls");
    printf("========== ALTERACAO ==========\n");
    ler_string("Digite o nome do contato: ", busca, 40);

    /* Mostra o contato antes de alterar, se encontrado */
    Agenda_pesquisar(ag, busca);

    printf("\nConfirma alteracao? (S/N): ");
    confirma = getch();
    if (confirma != 'S' && confirma != 's')
    {
        pausar("\nOperacao cancelada. Pressione qualquer tecla...");
        return;
    }

    printf("\n\n--- Novos dados ---\n");
    ler_string("Novo Nome     : ", nome,  40);
    ler_string("Novo Email    : ", email, 40);
    tel = ler_int  ("Novo Telefone : ");

    if (Agenda_alterar(ag, busca, nome, email, tel))
        pausar("Contato alterado com sucesso! Pressione qualquer tecla...");
    else
        pausar("Contato NAO encontrado. Pressione qualquer tecla...");
}

static void tela_consultar(Agenda *ag)
{
    system("cls");
    printf("========== CONSULTA ==========\n");
    Agenda_consultar(ag);
    printf("\nTotal de contatos: %d", Agenda_total(ag));
    pausar("\n\nPressione qualquer tecla para voltar...");
}

static void tela_excluir(Agenda *ag)
{
    char busca[40];
    char confirma;

    system("cls");
    printf("========== EXCLUSAO ==========\n");
    ler_string("Digite o nome do contato: ", busca, 40);

    Agenda_pesquisar(ag, busca);

    printf("\nConfirma exclusao? (S/N): ");
    confirma = getch();
    if (confirma != 'S' && confirma != 's')
    {
        pausar("\nOperacao cancelada. Pressione qualquer tecla...");
        return;
    }

    if (Agenda_excluir(ag, busca))
        pausar("\nContato excluido com sucesso! Pressione qualquer tecla...");
    else
        pausar("\nContato NAO encontrado. Pressione qualquer tecla...");
}

static void tela_pesquisar(Agenda *ag)
{
    char busca[40];

    system("cls");
    printf("========== PESQUISA ==========\n");
    ler_string("Digite o nome (ou inicio do nome): ", busca, 40);
    Agenda_pesquisar(ag, busca);
    pausar("\nPressione qualquer tecla para voltar...");
}

/* ----------------------------------------------------------
   main
   ---------------------------------------------------------- */
int main(void)
{
    Agenda ag;
    int op;

    Agenda_inicializar(&ag);

    do {
        system("cls");
        printf("**** AGENDA Clarissa e Maria Izabel ****\n");
        printf("  Total de contatos: %d\n", Agenda_total(&ag));
        printf("================================\n");
        printf("  1 - Incluir\n");
        printf("  2 - Alterar\n");
        printf("  3 - Consultar agenda\n");
        printf("  4 - Excluir\n");
        printf("  5 - Pesquisar\n");
        printf("  9 - Sair\n");
        printf("================================\n");
        op = ler_int("Opcao: ");

        switch (op)
        {
            case 1: tela_incluir  (&ag); break;
            case 2: tela_alterar  (&ag); break;
            case 3: tela_consultar(&ag); break;
            case 4: tela_excluir  (&ag); break;
            case 5: tela_pesquisar(&ag); break;
            case 9: break;
            default:
                pausar("Opcao invalida! Pressione qualquer tecla...");
        }
    } while (op != 9);

    Agenda_destruir(&ag);
    printf("\nAgenda encerrada. Ate logo!\n");
    return 0;
}
