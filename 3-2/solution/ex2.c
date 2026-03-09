#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 2
#define BUFFER_SIZE 256

int main(void) {
    char** words = NULL;
    size_t capacity = INITIAL_CAPACITY;
    size_t count = 0;

    char buffer[BUFFER_SIZE];

    words = malloc(capacity * sizeof(char*));
    if (!words) {
        fprintf(stderr, "malloc failed");
        return 1;
    }

    printf("Enter words (type 'quit' to stop):\n");

    while (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';  // remove newline

        if (strcmp(buffer, "quit") == 0) break;

        if (count == capacity) {
            capacity *= 2;
            char** temp = realloc(words, capacity * sizeof(char*));
            if (!temp) {
                perror("realloc failed");
                break;
            }
            words = temp;
        }

        words[count] = malloc(strlen(buffer) + 1);
        if (!words[count]) {
            perror("malloc failed");
            break;
        }

        strcpy(words[count], buffer);
        count++;
    }

    printf("\nYou entered:\n");
    for (size_t i = 0; i < count; i++) {
        printf("%zu: %s\n", i, words[i]);
        free(words[i]);
    }

    free(words);
    return 0;
}