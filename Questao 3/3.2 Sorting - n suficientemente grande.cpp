#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* ======================================================
   3.1 Clarissa e Izabel - Implementar os algoritmos de ordenação: BubbleSort, SelectionSort e InsertionSort para n suficientemente grande
   ====================================================== */
/* ====================================================== */

void gerarVetorAleatorio(int v[], int n) {
    for (int i = 0; i < n; i++) {
        v[i] = rand() % 100000;
    }
}

void imprimirVetor(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}



/* ======================================================
   BUBBLE SORT
   ======================================================
   Ideia:
   - Compara elementos vizinhos
   - "Empurra" o maior para o final
   - Pode parar antes se já estiver ordenado
*/
void bubbleSort(int v[], int n) {
    int temp;
    int houveTroca;

    for (int i = 0; i < n - 1; i++) {
        houveTroca = 0; // controle de otimização

        for (int j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                // troca
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;

                houveTroca = 1;
            }
        }

        // se não houve troca, já está ordenado
        if (houveTroca == 0) {
            break;
        }
    }
}

/* ======================================================
   SELECTION SORT
   ======================================================
   Ideia:
   - Procura o menor elemento
   - Coloca na posição correta
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

        // troca apenas se necessário
        if (minIndex != i) {
            temp = v[i];
            v[i] = v[minIndex];
            v[minIndex] = temp;
        }
    }
}

/* ======================================================
   INSERTION SORT
   ======================================================
   Ideia:
   - Insere cada elemento na posição correta
   - Funciona como ordenar cartas na mão
*/
void insertionSort(int v[], int n) {
    int chave, j;

    for (int i = 1; i < n; i++) {
        chave = v[i];
        j = i - 1;

        // desloca elementos maiores
        while (j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = chave;
    }
}

/* ======================================================
   FUNÇÃO PARA COPIAR VETORES
   (evita modificar o original)
   ====================================================== */
void copiarVetor(int destino[], int origem[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}

/* ======================================================
   FUNÇÃO PRINCIPAL
   ====================================================== */
int main() {
	
    int n = 10000;

    srand(time(NULL));

    int *vetor = malloc(n * sizeof(int));

    gerarVetorAleatorio(vetor, n);

    printf("Primeiros 10 elementos:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", vetor[i]);
    }
    


    /* -------- BUBBLE SORT -------- */
    copiarVetor(v1, original, n);
    printf("Bubble Sort\n");
    printf("Antes : ");
    imprimirVetor(v1, n);

    bubbleSort(v1, n);

    printf("Depois: ");
    imprimirVetor(v1, n);
    printf("\n");

    /* -------- SELECTION SORT -------- */
    copiarVetor(v2, original, n);
    printf("Selection Sort\n");
    printf("Antes : ");
    imprimirVetor(v2, n);

    selectionSort(v2, n);

    printf("Depois: ");
    imprimirVetor(v2, n);
    printf("\n");

    /* -------- INSERTION SORT -------- */
    copiarVetor(v3, original, n);
    printf("Insertion Sort\n");
    printf("Antes : ");
    imprimirVetor(v3, n);

    insertionSort(v3, n);

    printf("Depois: ");
    imprimirVetor(v3, n);
    printf("\n");

    return 0;
}

