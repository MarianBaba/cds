int hash(int k, int m) {
    return k % m;
}

int majority(int *array, int size) {
    int freq[100000] = {0};
    for (int i = 0; i < size; i++) {
        freq[array[i]]++;
        if (freq[array[i]] > size / 2) {
            return array[i];
        }
    }
    return -1;
}