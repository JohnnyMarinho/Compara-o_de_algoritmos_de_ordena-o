#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função BubbleSort
void bubbleSort(int vetor[], int tamanho) {
    int i, j, aux;
    int trocou;

    for (i = 0; i < tamanho - 1; i++) {
        trocou = 0; 
        for (j = 0; j < tamanho - 1 - i; j++) {
            if (vetor[j] > vetor[j + 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
                trocou = 1; // Houve troca nesta passagem
            }
        }

        // Se não fouve troca, o vetor está ordenado
        if (trocou == 0) {
            break;
        }
    }
}

// Função Insertion Sort
void insertionSort(int vetor[], int tamanho) {
    int i, chave, j;

    for (i = 1; i < tamanho; i++) {
        chave = vetor[i]; 
        
        j = i - 1;

        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j]; 
            j = j - 1;
        }
        
        vetor[j + 1] = chave;
    }
}

// Merge
void merge(int a[], int inicio, int meio, int fim) {
    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = a[inicio + i];
    for (j = 0; j < n2; j++)
        R[j] = a[meio + 1 + j];

    i = 0;
    j = 0;
    k = inicio;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

// Função Merge Sort
void mergeSort(int a[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        mergeSort(a, inicio, meio);
        mergeSort(a, meio + 1, fim);

        merge(a, inicio, meio, fim);
    }
}

// Função para imprimir o vetor
void printV(int vetor[], int tamanho) {
    int i;
    for (i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

//copia vetores para uso dos algoritmos
void copiaVetor(int origem[], int destino[], int tamanho){
    int i = 0;
    for(i = 0; i <= tamanho; i++){
        destino[i] = origem[i];
    }
}

//Le arquivo
int *lerVetorArquivo(const char *arquivoVetor, int *tamanho){
    FILE *arquivo = fopen(arquivoVetor, "r");
    if(arquivo == NULL){
        printf("Erro com leitura de arquivo %s \n", arquivoVetor);
        exit(1);
    }

    int capacidade = 10;
    int *vetor = malloc(capacidade * sizeof(int));
    int valor;
    *tamanho = 0;

    while(fscanf(arquivo, "%d", &valor) == 1){
        if(*tamanho >= capacidade){
            capacidade *= 2;
            vetor = realloc(vetor, capacidade * sizeof(int));
        }
        vetor[*tamanho] = valor;
        (*tamanho)++;
    }

    fclose(arquivo);
    return vetor;
}

int main() {
    int n;
    int *vetorBase = lerVetorArquivo("trinta_ordenado.txt", &n);

    int *vetorB = malloc(n * sizeof(int));
    int *vetorI = malloc(n * sizeof(int));
    int *vetorM = malloc(n * sizeof(int));

    copiaVetor(vetorBase, vetorB, n);
    copiaVetor(vetorBase, vetorI, n);
    copiaVetor(vetorBase, vetorM, n);
    
    clock_t inicio, fim;
    double tempo;

    //printf("Vetor base (%d elementos):\n", n);
    //printV(vetorBase, n);
    //printf("\n");

    //BubbleSort
    inicio = clock();
    bubbleSort(vetorB, n);
    fim = clock();
    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Bubble Sort: ");
    //printV(vetorB, n);
    printf("Tempo = %.6f segundos\n\n", tempo);

    //InsertionSort
    inicio = clock();
    insertionSort(vetorI, n);
    fim = clock();
    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Insertion Sort: ");
    //printV(vetorI, n);
    printf("Tempo = %.6f segundos\n\n", tempo);

    //MergeSort
    inicio = clock();
    mergeSort(vetorM, 0, n - 1);
    fim = clock();
    printf("MergeSort Sort: ");
    //printV(vetorM, n);
    printf("Tempo = %.6f segundos\n\n", tempo);

    free(vetorBase);
    free(vetorB);
    free(vetorI);
    free(vetorM);

    return 0;
}