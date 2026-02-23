#include <stdio.h>
#include <stdlib.h>

int* create_even_numbers(int count) {
    // TODO: Allocate an array of 'count' integers on the HEAP
    int* arr = malloc(count * sizeof(int));

    // Safety check: Ensure malloc succeeded
    if (arr == NULL) return NULL;

    for (int i = 0; i < count; i++) {
        arr[i] = i * 2;
    }

    // TODO: Return the pointer to the heap memory
    return arr;
}

int main() {
    int n = 5;
    int* my_evens = create_even_numbers(n);

    if (my_evens != NULL) {
        printf("The third even number is: %d\n", my_evens[2]);

        // TODO: End the lifetime of the array to avoid a memory leak
        free(my_evens);
    }
    return 0;
}