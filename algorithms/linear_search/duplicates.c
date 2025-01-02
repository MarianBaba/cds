int duplicates(int *array, int len) {
    int freq[10000] = {0};
    for (int i = 0; i < len; i++) {
        freq[array[i]]++;
    }
    for (int i = 0; i < len; i++) {
        if (freq[array[i]] > 1) {
            return 0; // true, has duplicates
        } 
    }
    return 1; // false, does not have duplicates
}