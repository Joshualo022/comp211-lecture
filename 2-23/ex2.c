#include <stdio.h>
#include <stdlib.h>

int main() {
    // We start with space for 2 items
    int* list = malloc(2 * sizeof(int));
    list[0] = 10;
    list[1] = 20;

    printf("Original list: %d, %d\n", list[0], list[1]);

    // TODO: Use realloc to grow the 'list' to hold 4 integers
    int* temp = realloc(list, 4 * sizeof(int));

    if (temp != NULL) {
        list = temp;
        list[2] = 30;
        list[3] = 40;
        printf("New items: %d, %d\n", list[2], list[3]);
    }

    // TODO: Clean up the memory
    free(list);

    return 0;
}