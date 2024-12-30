#include <stdio.h>
#include <stdbool.h>

bool linear_search(int arr[], int len, int target) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == target) {
            return true;
        }
    }
    return false;
}

int main() {
    int array[] = {1, 2, 3};
    printf("%d\n", array[0]); // fast access using indexes
    // elements are near each other, so cache is helpful (space locality)

    // but, if i need to insert a new element -> needs resizing
    // suppose i want to insert 4 at the end, i need to declare another array and copy the old elements
    int resized[4];
    for (int i = 0; i < 3; i++) { // O(n)
        resized[i] = array[i];
    }
    resized[3] = 4;

    printf("%d\n", resized[3]);

    int multi_dimensional[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    printf("%d\n", multi_dimensional[1][1]);

    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int target = 5;

    bool res = linear_search(a, 9, target);
    printf("%d\n", res);

    // 1 -> true
    // 0 -> false
    
    return 0;
}