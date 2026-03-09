#include <stdio.h>
#include <stdlib.h>

static int** alloc2d(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;

    int** a = malloc(sizeof(int*) * (size_t)rows);
    if (a == NULL) return NULL;

    for (int i = 0; i < rows; i++) {
        a[i] = malloc(sizeof(int) * (size_t)cols);
        if (a[i] == NULL) {
            for (int k = 0; k < i; k++) free(a[k]);
            free(a);
            return NULL;
        }
    }
    return a;
}

static void free2d(int** a, int rows) {
    if (a == NULL) return;
    for (int i = 0; i < rows; i++) free(a[i]);
    free(a);
}

static void die_bad_row(int r, int rows) {
    fprintf(stderr, "ERROR: row index out of bounds: r=%d for rows=%d\n", r,
            rows);
    exit(1);
}

void swap_rows(int** a, int rows, int r1, int r2) {
    if (a == NULL) {
        fprintf(stderr, "ERROR: swap_rows called with NULL array\n");
        exit(1);
    }
    if (r1 < 0 || r1 >= rows) die_bad_row(r1, rows);
    if (r2 < 0 || r2 >= rows) die_bad_row(r2, rows);

    int* tmp = a[r1];
    a[r1] = a[r2];
    a[r2] = tmp;
}

static void init_pattern(int** a, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            a[i][j] = i * 10 + j;
        }
    }
}

static void print2d(int** a, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d", a[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    const int rows = 5;
    const int cols = 6;

    int** a = alloc2d(rows, cols);
    if (a == NULL) {
        fprintf(stderr, "ERROR: alloc2d failed\n");
        return 1;
    }

    init_pattern(a, rows, cols);

    printf("Before swap_rows(a, %d, 1, 4):\n", rows);
    print2d(a, rows, cols);

    swap_rows(a, rows, 1, 4);

    printf("\nAfter swap:\n");
    print2d(a, rows, cols);

    free2d(a, rows);
    return 0;
}