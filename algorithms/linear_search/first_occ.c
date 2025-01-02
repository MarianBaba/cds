int first_occ(int *array, int len, int n) {
    for (int i = 0; i < len; i++) {
        if (array[i] == n) {
            return i;
        }
    }
    return -1;
}