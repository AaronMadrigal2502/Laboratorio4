#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int read_next_int(FILE *file, int *value) {
    int c = 0;

    do {
        c = fgetc(file);
        if (c == '#') {
            do {
                c = fgetc(file);
            } while (c != '\n' && c != EOF);
        }
    } while (isspace(c));

    if (c == EOF) {
        return 0;
    }

    ungetc(c, file);
    return fscanf(file, "%d", value) == 1;
}

/* Lee una imagen PGM P2 y reserva memoria dinamica para sus pixeles. */
unsigned char *read_pgm(const char *filename, int *width, int *height, int *max_val) {
    FILE *file = NULL;
    char magic_1 = '\0';
    char magic_2 = '\0';
    int total = 0;
    unsigned char *pixels = NULL;
    unsigned char *ptr = NULL;
    unsigned char *end = NULL;

    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: no se pudo abrir %s.\n", filename);
        return NULL;
    }

    if (fscanf(file, " %c%c", &magic_1, &magic_2) != 2 || magic_1 != 'P' || magic_2 != '2') {
        fprintf(stderr, "Error: el archivo no tiene formato PGM P2.\n");
        fclose(file);
        return NULL;
    }

    if (!read_next_int(file, width) || !read_next_int(file, height) || !read_next_int(file, max_val)) {
        fprintf(stderr, "Error: encabezado PGM incompleto.\n");
        fclose(file);
        return NULL;
    }

    if (*width <= 0 || *height <= 0 || *max_val <= 0 || *max_val > 255) {
        fprintf(stderr, "Error: dimensiones o valor maximo invalidos.\n");
        fclose(file);
        return NULL;
    }

    total = (*width) * (*height);
    pixels = malloc((size_t) total * sizeof(unsigned char));
    if (pixels == NULL) {
        fprintf(stderr, "Error: no se pudo reservar memoria para pixeles.\n");
        fclose(file);
        return NULL;
    }

    ptr = pixels;
    end = pixels + total;
    while (ptr < end) {
        int value = 0;
        if (!read_next_int(file, &value) || value < 0 || value > *max_val) {
            fprintf(stderr, "Error: pixel invalido o faltante.\n");
            free(pixels);
            fclose(file);
            return NULL;
        }
        *ptr = (unsigned char) value;
        ptr++;
    }

    fclose(file);
    return pixels;
}

/* Aplica un umbral T al arreglo de pixeles in-place usando punteros. */
void apply_threshold(unsigned char *pixels, int total, int threshold) {
    unsigned char *ptr = pixels;
    unsigned char *end = pixels + total;

    while (ptr < end) {
        if (*ptr >= threshold) {
            *ptr = 255;
        } else {
            *ptr = 0;
        }
        ptr++;
    }
}

/* Genera el negativo de un arreglo de pixeles en un nuevo arreglo usando punteros. */
unsigned char *make_negative(unsigned char *pixels, int total) {
    unsigned char *negative = NULL;
    unsigned char *src = pixels;
    unsigned char *dst = NULL;
    unsigned char *end = pixels + total;

    negative = malloc((size_t) total * sizeof(unsigned char));
    if (negative == NULL) {
        fprintf(stderr, "Error: no se pudo reservar memoria para el negativo.\n");
        return NULL;
    }

    dst = negative;
    while (src < end) {
        *dst = (unsigned char) (255 - *src);
        src++;
        dst++;
    }

    return negative;
}

/* Copia un arreglo de pixeles. */
unsigned char *copy_pixels(const unsigned char *pixels, int total) {
    unsigned char *copy = NULL;
    const unsigned char *src = pixels;
    const unsigned char *end = pixels + total;
    unsigned char *dst = NULL;

    copy = malloc((size_t) total * sizeof(unsigned char));
    if (copy == NULL) {
        fprintf(stderr, "Error: no se pudo reservar memoria para copia.\n");
        return NULL;
    }

    dst = copy;
    while (src < end) {
        *dst = *src;
        src++;
        dst++;
    }

    return copy;
}

/* Escribe un arreglo de pixeles como imagen PGM P2. */
void write_pgm(const char *filename, unsigned char *pixels, int width, int height, int max_val) {
    FILE *file = NULL;
    unsigned char *ptr = pixels;

    file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: no se pudo escribir %s.\n", filename);
        return;
    }

    fprintf(file, "P2\n%d %d\n%d\n", width, height, max_val);
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            fprintf(file, "%u ", (unsigned int) *ptr);
            ptr++;
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

/* Calcula e imprime estadisticas del original y del arreglo umbralizado. */
void print_stats(unsigned char *original, unsigned char *thresholded, int total) {
    unsigned char *orig_ptr = original;
    unsigned char *thr_ptr = thresholded;
    unsigned char *orig_end = original + total;
    int white = 0;
    int black = 0;
    unsigned long sum = 0UL;
    double average = 0.0;

    while (orig_ptr < orig_end) {
        sum += (unsigned long) *orig_ptr;

        if (*thr_ptr == 255) {
            white++;
        } else if (*thr_ptr == 0) {
            black++;
        }

        orig_ptr++;
        thr_ptr++;
    }

    average = (double) sum / (double) total;

    printf("Pixeles blancos en imagen umbralizada: %d\n", white);
    printf("Pixeles negros en imagen umbralizada: %d\n", black);
    printf("Promedio de pixeles originales: %.2f\n", average);
}

int main(void) {
    int width = 0;
    int height = 0;
    int max_val = 0;
    int threshold = 0;
    int total = 0;
    unsigned char *original = NULL;
    unsigned char *pixels = NULL;
    unsigned char *negative = NULL;

    original = read_pgm("input.pgm", &width, &height, &max_val);
    if (original == NULL) {
        return EXIT_FAILURE;
    }

    total = width * height;
    pixels = copy_pixels(original, total);
    if (pixels == NULL) {
        free(original);
        return EXIT_FAILURE;
    }

    printf("Ingrese el valor de umbral T: ");
    if (scanf("%d", &threshold) != 1 || threshold < 0 || threshold > max_val) {
        fprintf(stderr, "Error: el umbral debe estar entre 0 y %d.\n", max_val);
        free(original);
        free(pixels);
        return EXIT_FAILURE;
    }

    apply_threshold(pixels, total, threshold);
    negative = make_negative(pixels, total);
    if (negative == NULL) {
        free(original);
        free(pixels);
        return EXIT_FAILURE;
    }

    write_pgm("output_threshold.pgm", pixels, width, height, max_val);
    write_pgm("output_negative.pgm", negative, width, height, max_val);
    print_stats(original, pixels, total);

    free(original);
    free(pixels);
    free(negative);

    return EXIT_SUCCESS;
}
