#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *fu(char *string) {
    int freq[256] = {0}; // -> this initialises all the cells in the array to zero
    // the previous is an array of integers that represents the frequences
    // of all the elements in the ascii charset
    int size = strlen(string);

    for (int i = 0; i < size; i++) {
        freq[(unsigned char)string[i]]++;
    }

    for(int i = 0; i < size; i++) {
        if ((unsigned char)freq[string[i]] == 1) {
            char *res = malloc(sizeof(char));
            res = &string[i];
            return res;
        }
    }
    return NULL;
}


int main() {

    char *string = "leetcode";
    char *res = fu(string);
    if (res == NULL) {
        printf("%d\n", -1);
    } else {
        printf("%c\n", *res);
    }

    return 0;
}