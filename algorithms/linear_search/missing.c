#include <stdlib.h>

int missing(int *array, int range, int size) {
    int *freq = calloc(10001, sizeof(int));
    for (int i = 0; i < size; i++) {
        freq[array[i]]++;
    }
    for (int i = 0; i < size; i++) {
        if (freq[i] == 0) {
            return array[i];
        }
    }
    return -1;
} 