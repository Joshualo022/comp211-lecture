#include <stdio.h>
#include <stdlib.h>

/*
 * alloc2d
 * -------
 * Dynamically allocates a 2D array of integers with the given
 * number of rows and columns.
 *
 * Parameters:
 *   rows - number of rows (must be > 0)
 *   cols - number of columns (must be > 0)
 *
 * Returns:
 *   Pointer to an array of int* (int**), where each row is
 *   separately allocated.
 *
 *   Returns NULL if:
 *     - rows <= 0
 *     - cols <= 0
 *     - any allocation fails
 */
static int** alloc2d(int rows, int cols) {
    /* TODO */
    return NULL;
}

/*
 * free2d
 * ------
 * Frees a 2D array previously allocated by alloc2d().
 *
 * Parameters:
 *   a    - the array returned by alloc2d() (may be NULL)
 *   rows - number of rows originally requested
 *
 * Behavior:
 *   - Safely does nothing if a == NULL.
 *   - Frees each row, then frees the row-pointer array.
 */
static void free2d(int** a, int rows) { /* TODO */ }

static void die_bad_row(int r, int rows) {
    fprintf(stderr, "ERROR: row index out of bounds: r=%d for rows=%d\n", r,
            rows);
    exit(1);
}

/*
 * swap_rows
 * ---------
 * Swaps two rows of a dynamically allocated 2D array in O(1) time.
 *
 * Parameters:
 *   a    - 2D array created by alloc2d()
 *   rows - total number of rows in the array
 *   r1   - index of the first row to swap
 *   r2   - index of the second row to swap
 *
 * Behavior:
 *   - Validates that 'a' is not NULL.
 *   - Validates that r1 and r2 are within bounds [0, rows).
 *   - On error, prints a message to stderr and terminates.
 *
 * Performance:
 *   This operation is O(1) because it swaps row pointers,
 *   NOT the contents of the rows.
 *
 *   Only these pointers move:
 *       a[r1] <--> a[r2]
 *
 *   The integer data itself is untouched.
 *
 * Example:
 *   swap_rows(a, rows, 0, 3);   // exchanges row 0 and row 3
 */
void swap_rows(int** a, int rows, int r1, int r2) {
    /* TODO: bounds check, then swap a[r1] and a[r2] */
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