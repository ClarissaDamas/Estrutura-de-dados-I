#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N          100000   /* tamanho do vetor                  */
#define VALOR_MAX  100000  /* valores entre 0 e 99.999          */


typedef struct {
    long long comparacoes;
    long long atribuicoes;
    double    tempo_ms;
} Metricas;

/* ============================================================
   GERACAO E COPIA DE VETORES
   ============================================================ */

void gerarVetorAleatorio(int v[], int n) {
    for (int i = 0; i < n; i++) {
        v[i] = rand() % VALOR_MAX;
    }
}

void copiarVetor(int destino[], const int origem[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}


void bubbleSort(int v[], int n, Metricas *m) {
    int temp, houveTroca;

    for (int i = 0; i < n - 1; i++) {
        houveTroca = 0;

        for (int j = 0; j < n - i - 1; j++) {

            m->comparacoes++;               /* if (v[j] > v[j+1]) */
            if (v[j] > v[j + 1]) {

                temp       = v[j];
                v[j]       = v[j + 1];
                v[j + 1]   = temp;
                m->atribuicoes += 3;        /* troca = 3 atribuicoes */
                houveTroca = 1;
            }
        }

        if (houveTroca == 0) break;
    }
}


void selectionSort(int v[], int n, Metricas *m) {
    int minIndex, temp;

    for (int i = 0; i < n - 1; i++) {
        minIndex = i;

        for (int j = i + 1; j < n; j++) {

            m->comparacoes++;               /* if (v[j] < v[minIndex]) */
            if (v[j] < v[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            temp            = v[i];
            v[i]            = v[minIndex];
            v[minIndex]     = temp;
            m->atribuicoes += 3;            /* troca = 3 atribuicoes */
        }
    }
}


void insertionSort(int v[], int n, Metricas *m) {
    int chave, j;

    for (int i = 1; i < n; i++) {

        chave = v[i];
        m->atribuicoes++;                   /* chave = v[i]: salvar elemento */
        j = i - 1;

        while (j >= 0) {

            m->comparacoes++;               /* v[j] > chave */
            if (v[j] <= chave) break;       /* condicao falsa: sai do loop  */

            v[j + 1] = v[j];
            m->atribuicoes++;               /* deslocamento = 1 atribuicao  */
            j--;
        }

        v[j + 1] = chave;
        m->atribuicoes++;                   /* repor chave na posicao certa */
    }
}

/* ============================================================
   MEDICAO DE TEMPO
   ============================================================ */
double medirTempo_ms(clock_t inicio, clock_t fim) {
    return (double)(fim - inicio) / CLOCKS_PER_SEC * 1000.0;
}

/* ============================================================
   IMPRESSAO DO RELATORIO DE UM ALGORITMO
   ============================================================ */
void imprimirResultado(const char *nome, Metricas m) {
    long long total = m.comparacoes + m.atribuicoes;
    printf("  +--------------------------------------------------+\n");
    printf("  | %-48s |\n", nome);
    printf("  +--------------------------------------------------+\n");
    printf("  | Tempo de execucao   : %10.2f ms             |\n", m.tempo_ms);
    printf("  | Comparacoes         : %15lld          |\n", m.comparacoes);
    printf("  | Atribuicoes         : %15lld          |\n", m.atribuicoes);
    printf("  | Total de operacoes  : %15lld          |\n", total);
    printf("  +--------------------------------------------------+\n\n");
}

/* ============================================================
   FUNCAO PRINCIPAL — EXPERIMENTO
   ============================================================ */
int main() {
    srand((unsigned int)time(NULL));

    /* --- Alocacao dinamica dos vetores --- */
    int *original = (int *)malloc(N * sizeof(int));
    int *v1       = (int *)malloc(N * sizeof(int));
    int *v2       = (int *)malloc(N * sizeof(int));
    int *v3       = (int *)malloc(N * sizeof(int));

    if (original == NULL || v1 == NULL || v2 == NULL || v3 == NULL) {
        fprintf(stderr, "[ERRO] Falha na alocacao de memoria.\n");
        free(original); free(v1); free(v2); free(v3);
        return 1;
    }

    /* Gera o vetor UMA unica vez — todos os algoritmos
     * recebem uma copia identica para comparacao justa. */
    gerarVetorAleatorio(original, N);

    clock_t  inicio, fim;
    Metricas mb = {0, 0, 0.0};   /* metricas do Bubble Sort    */
    Metricas ms = {0, 0, 0.0};   /* metricas do Selection Sort */
    Metricas mi = {0, 0, 0.0};   /* metricas do Insertion Sort */

    /* ==========================================================
       BUBBLE SORT
       ========================================================== */
    copiarVetor(v1, original, N);
    inicio = clock();
    bubbleSort(v1, N, &mb);
    fim    = clock();
    mb.tempo_ms = medirTempo_ms(inicio, fim);

    /* ==========================================================
       SELECTION SORT
       ========================================================== */
    copiarVetor(v2, original, N);
    inicio = clock();
    selectionSort(v2, N, &ms);
    fim    = clock();
    ms.tempo_ms = medirTempo_ms(inicio, fim);

    /* ==========================================================
       INSERTION SORT
       ========================================================== */
    copiarVetor(v3, original, N);
    inicio = clock();
    insertionSort(v3, N, &mi);
    fim    = clock();
    mi.tempo_ms = medirTempo_ms(inicio, fim);

    /* ==========================================================
       RELATORIO FINAL
       ========================================================== */
    printf("\n");
    printf("  ====================================================\n");
    printf("  EXPERIMENTO: Ordenacao com Contagem de Operacoes\n");
    printf("  Tamanho do vetor : n = %d elementos\n", N);
    printf("  Limite O(n^2)    : %lld comparacoes\n",
           (long long)N * (N - 1) / 2);
    printf("  ====================================================\n\n");

    imprimirResultado("Bubble Sort",    mb);
    imprimirResultado("Selection Sort", ms);
    imprimirResultado("Insertion Sort", mi);

    /* Tabela comparativa resumida */
    printf("  %-16s  %10s  %15s  %15s  %15s\n",
           "Algoritmo", "Tempo(ms)", "Comparacoes", "Atribuicoes", "Total ops");
    printf("  %-16s  %10s  %15s  %15s  %15s\n",
           "----------------", "----------",
           "---------------", "---------------", "---------------");
    printf("  %-16s  %10.2f  %15lld  %15lld  %15lld\n",
           "Bubble Sort",    mb.tempo_ms, mb.comparacoes, mb.atribuicoes,
           mb.comparacoes + mb.atribuicoes);
    printf("  %-16s  %10.2f  %15lld  %15lld  %15lld\n",
           "Selection Sort", ms.tempo_ms, ms.comparacoes, ms.atribuicoes,
           ms.comparacoes + ms.atribuicoes);
    printf("  %-16s  %10.2f  %15lld  %15lld  %15lld\n",
           "Insertion Sort", mi.tempo_ms, mi.comparacoes, mi.atribuicoes,
           mi.comparacoes + mi.atribuicoes);
    printf("\n");

    free(original); free(v1); free(v2); free(v3);
    return 0;
}
