int check(int *array, int target, int size) {
    int i = 0;
    while (array[i] <= target && i < size) {
        if (array[i] == target) {
            return 0; // true
        }
        i++;
    }
    return 1;
}

int check_bs(int *array, int target, int size) {
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int middle = low + ((high - low) / 2);
        if (array[middle] == target) {
            return 0; // true
        }
        if (array[middle] > target) {
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }
    return 1; // false
}