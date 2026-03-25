#include "array_utils.h"

int array_sum(const int arr[], int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += arr[i];
    }
    return sum;
}

int array_max_index(const int arr[], int length) {
    if (length == 0) {
        return -1;
    }
    int max_index = 0;
    for (int i = 1; i < length; i++) {
        if (arr[i] > arr[max_index]) {
            max_index = i;
        }
    }
    return max_index;
}

void array_clamp_nonnegative(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        if (arr[i] < 0) {
            arr[i] = 0;
        }
    }
}