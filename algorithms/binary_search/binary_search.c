#include <stdio.h>


int binary_search(int *array, int start, int end, int target) {
    int low = start;
    int high = end;

    while (low <= high) {
        int middle = low + ((high - low) / 2);
        if (array[middle] == target) {
            return middle;
        } 
        if (array[middle] > target) {
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }
    return - 1;
}

int main() {

    int arr[] = {1, 2, 3, 8, 8, 8, 9};
    int target = 8;
    int size = 6;

    int min = binary_search(arr, 0, size - 1, target);
    int max = min;

    int res = min;
    while (res != -1) {
        res = binary_search(arr, 0, res - 1, target);
        if (res < min && res != -1) {
            min = res;
        }
    }

    res = max;
    while (res != -1) {
        res = binary_search(arr, res+1, size - 1, target);
        if (res > max && res != -1) {
            max = res;
        }
    }

    printf("min: %d\n", min);
    printf("max: %d\n", max);

    return 0;
}