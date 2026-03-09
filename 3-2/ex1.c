#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 5
#define NEW_SIZE 10

int main(void) {
    int* arr = malloc(INITIAL_SIZE * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "malloc failed");
        return 1;
    }

    // Initialize some data
    for (int i = 0; i < INITIAL_SIZE; i++) {
        arr[i] = i + 1;
    }

    printf("Original array: ");
    for (int i = 0; i < INITIAL_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Try to grow the array
    size_t new_size = NEW_SIZE * sizeof(int);
    int* tmp = realloc(arr, new_size);
    if (tmp == NULL) {
        // realloc failed — arr is still valid
        fprintf(stderr, "Error: realloc failed, keeping original memory.\n");
        free(arr);  // must free the original block to avoid leaks
        return 1;
    }

    // realloc succeeded — use the new pointer
    arr = tmp;

    // Initialize new elements
    for (int i = INITIAL_SIZE; i < NEW_SIZE; i++) {
        arr[i] = i + 1;
    }

    printf("Resized array: ");
    for (int i = 0; i < NEW_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Clean up
    free(arr);
    return 0;
}
