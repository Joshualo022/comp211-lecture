#include "pointer.h"
int addThroughPointers(const int* a, const int* b, int* result) {
    if (!a || !b || !result) {
        return 0;
    }
    *result = *a + *b;
    return 1;
}
