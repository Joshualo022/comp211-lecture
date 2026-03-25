#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_SPECIES_LEN 50

typedef struct {
    char name[MAX_NAME_LEN];
    char species[MAX_SPECIES_LEN];
    int age;
    int weight;
} Pet;

typedef struct {
    Pet* data;
    size_t size;
    size_t capacity;
} PetVec;

/*
 * Initialize the vector so it starts empty.
 * data is NULL because no array has been allocated yet.
 */
void petvec_init(PetVec* v) {
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

/*
 * Free the memory used by the vector.
 * After freeing, reset the fields so the vector is safe to reuse.
 */
void petvec_free(PetVec* v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

/*
 * Grow the array if it is full.
 *
 * Returns:
 *   1 on success
 *   0 if memory allocation fails
 */
int petvec_grow(PetVec* v) {
    if (v->size < v->capacity) {
        return 1;  // No need to grow
    }

    size_t new_capacity = (v->capacity == 0) ? 4 : v->capacity * 2;
    Pet* new_data = realloc(v->data, new_capacity * sizeof(Pet));
    if (new_data == NULL) {
        return 0;  // Allocation failed
    }

    v->data = new_data;
    v->capacity = new_capacity;
    return 1;  // Successfully grew the array
}

/*
 * Add a pet to the end of the vector.
 *
 * Returns:
 *   1 on success
 *   0 on allocation failure
 */
int petvec_push(PetVec* v, Pet p) {
    if (!petvec_grow(v)) {
        return 0;
    }

    v->data[v->size] = p;
    v->size = v->size + 1;

    return 1;
}

/*
 * Get a pointer to the pet at the given index.
 *
 * Returns:
 *   pointer to the Pet if index is valid
 *   NULL if index is out of range
 */
Pet* petvec_get(const PetVec* v, size_t index) {
    if (index >= v->size) {
        return NULL;  // Index out of range
    }
    return &v->data[index];
}

/*
 * Insert a pet at a specific index.
 *
 * Valid insert positions are 0 through size.
 * Inserting at size means "append to the end".
 *
 * Returns:
 *   1 on success
 *   0 on invalid index or allocation failure
 */
int petvec_insert(PetVec* v, size_t index, Pet p) {
    if (index > v->size) {
        return 0;  // Invalid index
    }

    if (!petvec_grow(v)) {
        return 0;  // Allocation failed
    }

    // Shift elements to the right to make space for the new pet
    for (size_t i = v->size; i > index; i--) {
        v->data[i] = v->data[i - 1];
    }

    v->data[index] = p;
    v->size = v->size + 1;

    return 1;
}

/*
 * Remove the pet at a specific index.
 *
 * Returns:
 *   1 on success
 *   0 if index is out of range
 */
int petvec_remove(PetVec* v, size_t index) {
    if (index >= v->size) {
        return 0;  // Index out of range
    }

    // Shift elements to the left to fill the gap
    for (size_t i = index; i < v->size - 1; i++) {
        v->data[i] = v->data[i + 1];
    }

    v->size = v->size - 1;
    return 1;
}

/*
 * Find the first pet with the given name.
 *
 * Returns:
 *   pointer to the matching Pet
 *   NULL if no match is found
 */
Pet* petvec_find(const PetVec* v, const char* name) {
    for (size_t i = 0; i < v->size; i++) {
        if (strcmp(v->data[i].name, name) == 0) {
            return &v->data[i];
        }
    }
    return NULL;
}

void petvec_print(const PetVec* v) {
    size_t i;

    printf("PetVec\n");
    printf("  size = %zu\n", v->size);
    printf("  capacity = %zu\n", v->capacity);

    for (i = 0; i < v->size; i++) {
        printf("  [%zu] name=\"%s\", age=%d\n", i, v->data[i].name,
               v->data[i].age);
    }
}

int main(void) {
    PetVec pets;
    Pet p1 = {"Buddy", "dog", 3, 25};
    Pet p2 = {"Mittens", "cat", 5, 10};
    Pet p3 = {"Charlie", "goat", 2, 40};
    Pet p4 = {"Rocky", "bird", 4, 2};

    petvec_init(&pets);

    if (!petvec_push(&pets, p1)) {
        fprintf(stderr, "Failed to push Buddy\n");
        petvec_free(&pets);
        return 1;
    }

    if (!petvec_push(&pets, p2)) {
        fprintf(stderr, "Failed to push Mittens\n");
        petvec_free(&pets);
        return 1;
    }

    if (!petvec_push(&pets, p3)) {
        fprintf(stderr, "Failed to push Charlie\n");
        petvec_free(&pets);
        return 1;
    }

    printf("After pushing 3 pets:\n");
    petvec_print(&pets);
    printf("\n");

    if (!petvec_insert(&pets, 1, p4)) {
        fprintf(stderr, "Failed to insert Rocky at index 1\n");
        petvec_free(&pets);
        return 1;
    }

    printf("After inserting Luna at index 1:\n");
    petvec_print(&pets);
    printf("\n");

    Pet* pet_at_index = petvec_get(&pets, 2);
    if (pet_at_index != NULL) {
        printf("Pet at index 2: %s, age %d\n", pet_at_index->name,
               pet_at_index->age);
    } else {
        printf("Index 2 is out of range\n");
    }
    printf("\n");

    Pet* found = petvec_find(&pets, "Buddy");
    if (found != NULL) {
        printf("Found pet named Buddy: age %d\n", found->age);
    } else {
        printf("Buddy was not found\n");
    }
    printf("\n");

    if (!petvec_remove(&pets, 2)) {
        fprintf(stderr, "Failed to remove pet at index 2\n");
        petvec_free(&pets);
        return 1;
    }

    printf("After removing the pet at index 2:\n");
    petvec_print(&pets);
    printf("\n");

    petvec_free(&pets);
    return 0;
}