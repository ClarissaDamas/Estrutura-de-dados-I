/*
 * ============================================================
 *  Clarissa e Izabel
 * ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N          100000   /* tamanho do vetor                  */
#define VALOR_MAX  100000  /* valores entre 0 e 99.999          */


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


/*
 * BUBBLE SORT
 */
void bubbleSort(int v[], int n) {
    int temp, houveTroca;

    for (int i = 0; i < n - 1; i++) {
        houveTroca = 0;

        for (int j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                temp       = v[j];
                v[j]       = v[j + 1];
                v[j + 1]   = temp;
                houveTroca = 1;
            }
        }

        if (houveTroca == 0) break;
    }
}

/*
 * SELECTION SORT
 */
void selectionSort(int v[], int n) {
    int minIndex, temp;

    for (int i = 0; i < n - 1; i++) {
        minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            temp            = v[i];
            v[i]            = v[minIndex];
            v[minIndex]     = temp;
        }
    }
}

/*
 * INSERTION SORT
 */
void insertionSort(int v[], int n) {
    int chave, j;

    for (int i = 1; i < n; i++) {
        chave = v[i];
        j     = i - 1;

        while (j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = chave;
    }
}

/*
 * mede o tempo em milisegundo
 */
double medirTempo_ms(clock_t inicio, clock_t fim) {
    return (double)(fim - inicio) / CLOCKS_PER_SEC * 1000.0;
}

/*
 * funcao principal
 */
int main() {
    /* --- Semente aleatoria baseada no tempo ---
     * Garante um vetor diferente a cada execucao.           */
    srand((unsigned int)time(NULL));

    /* --- Alocacao dinamica ---
     * Vetores de 10.000 ints = ~40 KB cada.
     *USANDO malloc() pq arrays estaticos grandes podem
     *causar o stack overflow que aprrendemos na aula.                    */
    int *original = (int *)malloc(N * sizeof(int));
    int *v1       = (int *)malloc(N * sizeof(int));
    int *v2       = (int *)malloc(N * sizeof(int));
    int *v3       = (int *)malloc(N * sizeof(int));


    if (original == NULL || v1 == NULL || v2 == NULL || v3 == NULL) {
        fprintf(stderr, "[ERRO] Falha na alocacao de memoria.\n");
        free(original);
        free(v1);
        free(v2);
        free(v3);
        return 1;
    }


    gerarVetorAleatorio(original, N);


    clock_t inicio, fim;
    double  tempo_bubble, tempo_selection, tempo_insertion;

    /* ==========================================================
       BUBBLE SORT
       ========================================================== */
    copiarVetor(v1, original, N);
    inicio         = clock();
    bubbleSort(v1, N);
    fim            = clock();
    tempo_bubble   = medirTempo_ms(inicio, fim);

    /* ==========================================================
       SELECTION SORT
       ========================================================== */
    copiarVetor(v2, original, N);
    inicio          = clock();
    selectionSort(v2, N);
    fim             = clock();
    tempo_selection = medirTempo_ms(inicio, fim);

    /* ==========================================================
       INSERTION SORT
       ========================================================== */
    copiarVetor(v3, original, N);
    inicio          = clock();
    insertionSort(v3, N);
    fim             = clock();
    tempo_insertion = medirTempo_ms(inicio, fim);

    printf("============================================================\n");
    printf("  EXPERIMENTO: Tempo de Execucao — Algoritmos de Ordenacao\n");
    printf("  Tamanho do vetor : n = %d elementos\n", N);
    printf("  Intervalo valores: [0, %d]\n", VALOR_MAX - 1);
    printf("============================================================\n\n");

    printf("  %-16s  %10s\n", "Algoritmo", "Tempo (ms)");
    printf("  %-16s  %10s\n", "----------------", "----------");
    printf("  %-16s  %10.2f ms\n", "Bubble Sort",    tempo_bubble);
    printf("  %-16s  %10.2f ms\n", "Selection Sort", tempo_selection);
    printf("  %-16s  %10.2f ms\n", "Insertion Sort", tempo_insertion);

    printf("\n");
    printf("  Todos os algoritmos ordenaram o mesmo vetor original.\n");
    printf("  Limite teorico de comparacoes O(n^2): %lld\n",
           (long long)N * (N - 1) / 2);
    printf("============================================================\n");

    /* --- Liberacao de memoria --- */
    free(original);
    free(v1);
    free(v2);
    free(v3);

    return 0;
}
