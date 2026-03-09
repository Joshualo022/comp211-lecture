#include <stdio.h>
#include <stdlib.h>

static inline size_t idx(size_t i, size_t j, size_t cols) {
    return i * cols + j;
}

static inline int in_bounds(int i, int j, int rows, int cols) {
    return (i >= 0 && i < rows && j >= 0 && j < cols);
}

static void die_oob(const char* fn, int i, int j, int rows, int cols) {
    fprintf(stderr,
            "ERROR: %s: index out of bounds (i=%d, j=%d) for rows=%d cols=%d\n",
            fn, i, j, rows, cols);
    exit(1);
}

void init_zero(int* grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[idx(i, j, cols)] = 0;
        }
    }
}

void grid_set(int* grid, int rows, int cols, int i, int j, int value) {
    if (!in_bounds(i, j, rows, cols)) {
        die_oob("grid_set", i, j, rows, cols);
    }
    grid[idx(i, j, cols)] = value;
}

int grid_get(const int* grid, int rows, int cols, int i, int j) {
    if (!in_bounds(i, j, rows, cols)) {
        die_oob("grid_get", i, j, rows, cols);
    }
    return grid[idx(i, j, cols)];
}

static void print_grid(const int* grid, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d", grid[idx(i, j, cols)]);
        }
        printf("\n");
    }
}

int main(void) {
    const int rows = 4;
    const int cols = 6;

    int* grid = malloc(sizeof(int) * rows * cols);
    if (grid == NULL) {
        fprintf(stderr, "ERROR: malloc failed\n");
        return 1;
    }

    init_zero(grid, rows, cols);

    grid_set(grid, rows, cols, 0, 0, 5);
    grid_set(grid, rows, cols, 3, 5, 99);
    grid_set(grid, rows, cols, 1, 2, -7);

    printf("Sanity checks:\n");
    printf("grid[0][0] = %d (expected 5)\n", grid_get(grid, rows, cols, 0, 0));
    printf("grid[3][5] = %d (expected 99)\n", grid_get(grid, rows, cols, 3, 5));
    printf("grid[1][2] = %d (expected -7)\n", grid_get(grid, rows, cols, 1, 2));

    printf("\nGrid contents:\n");
    print_grid(grid, rows, cols);

    free(grid);
    return 0;
}