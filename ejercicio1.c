#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Encuentra la secuencia de 1s consecutivos mas larga en la matriz,
 * tratandola como un arreglo lineal contiguo.
 */
void findLargestLine(int **matrix, int size, int *result) {
    int total = size * size;
    int current = 0;
    int largest = 0;
    int *ptr = *(matrix + 0);
    int *end = ptr + total;

    while (ptr < end) {
        if (*ptr == 1) {
            current++;
            if (current > largest) {
                largest = current;
            }
        } else {
            current = 0;
        }
        ptr++;
    }

    *result = largest;
}

/* Reserva memoria dinamica para una matriz cuadrada contigua. */
void allocateMatrix(int ***matrix, int size) {
    int **rows = NULL;
    int *data = NULL;

    rows = malloc((size_t) size * sizeof(int *));
    if (rows == NULL) {
        fprintf(stderr, "Error: no se pudo reservar memoria para las filas.\n");
        exit(EXIT_FAILURE);
    }

    data = malloc((size_t) size * (size_t) size * sizeof(int));
    if (data == NULL) {
        free(rows);
        fprintf(stderr, "Error: no se pudo reservar memoria para los datos.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        *(rows + i) = data + (i * size);
    }

    *matrix = rows;
}

/* Llena la matriz con valores binarios aleatorios. */
void fillMatrix(int **matrix, int size) {
    int total = size * size;
    int *ptr = *(matrix + 0);
    int *end = ptr + total;

    while (ptr < end) {
        *ptr = rand() % 2;
        ptr++;
    }
}

/* Imprime la matriz en stdout. */
void printMatrix(int **matrix, int size) {
    printf("Matriz (%dx%d):\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

/* Libera la memoria asignada a la matriz contigua. */
void freeMatrix(int **matrix, int size) {
    (void) size;
    if (matrix != NULL) {
        free(*(matrix + 0));
        free(matrix);
    }
}

int main(void) {
    int size = 0;
    int largestLine = 0;
    int **matrix = NULL;

    printf("Ingrese el tamano de la matriz cuadrada: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        fprintf(stderr, "Error: el tamano debe ser un entero positivo.\n");
        return EXIT_FAILURE;
    }

    srand((unsigned int) time(NULL));

    allocateMatrix(&matrix, size);
    fillMatrix(matrix, size);
    printMatrix(matrix, size);
    findLargestLine(matrix, size, &largestLine);

    printf("El tamano de la secuencia de 1s mas grande es: %d\n", largestLine);

    freeMatrix(matrix, size);

    return EXIT_SUCCESS;
}
