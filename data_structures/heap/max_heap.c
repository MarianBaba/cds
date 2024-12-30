#include <stdio.h>
#include <stdlib.h>

struct heap {
    int *array; //pointer to integer can be used as array
    int size; // number of elements currently in the heap
    int capacity; // maximum number of elements the heap can currently hold
    int insert_index; // the next available index where to insert an element
};

int peek(struct heap *max_heap) {
    if (max_heap->size == 0) {
        printf("heap is empty, exiting...\n");
        exit(1);
    }
    return max_heap->array[0];
};

struct heap *create_max_heap(int capacity) {
    struct heap *max_heap = malloc(sizeof(struct heap));
    max_heap->array = malloc(sizeof(int) * capacity);
    max_heap->capacity = capacity;
    max_heap->size = 0;
    max_heap->insert_index = 0;
    return max_heap;
};

void double_capacity(struct heap *max_heap) {
    max_heap->capacity *= 2;
    max_heap->array = reallocf(max_heap->array, max_heap->capacity);
    return;
};

void heapify_up(struct heap* max_heap, int index) {
    for (int i = index; i >= 0; i = (i - 1) / 2) {
        int parent = max_heap->array[i];
        int right_child = max_heap->array[(i * 2) + 2];

        if (right_child > parent) {
            int tmp = max_heap->array[(i * 2) + 2];
            max_heap->array[(i * 2) + 2] = max_heap->array[i];
            max_heap->array[i] = tmp;
        }

        parent = max_heap->array[i];
        int left_child = max_heap->array[(i * 2) + 1];
        if (left_child > parent) {
            int tmp = max_heap->array[(i * 2) + 1];
            max_heap->array[(i * 2) + 1] = max_heap->array[i];
            max_heap->array[i] = tmp;
        }
        if (i == 0) {
            i--;
        }
    }
};

void insert(struct heap *max_heap, int data) {
    int index = max_heap->insert_index;
    max_heap->array[max_heap->insert_index] = data;
    max_heap->insert_index++;
    max_heap->size++;
    if (max_heap->size == max_heap->capacity) {
        double_capacity(max_heap);
    }
    heapify_up(max_heap, index);
};

void heapify_down(struct heap *max_heap) {
    int last_internal_node_index = (max_heap->insert_index-1) / 2;
    for (int i = 0; i <= last_internal_node_index; i++) {
        int parent = max_heap->array[i];
        int left_child = max_heap->array[(i * 2) + 1];

        if (left_child > parent) {
            int tmp = max_heap->array[i];
            max_heap->array[i] = max_heap->array[(i * 2) + 1];
            max_heap->array[(i * 2) + 1] = tmp;
        }

        parent = max_heap->array[i];
        int right_child = max_heap->array[(i * 2) + 2];
        if (right_child > parent) {
            int tmp = max_heap->array[i];
            max_heap->array[i] = max_heap->array[(i * 2) + 2];
            max_heap->array[(i * 2) + 2] = tmp;
        }
    }
};

int extract_max(struct heap *max_heap) {
    if (max_heap->size == 0) {
        printf("empty heap, exiting...\n");
        exit(1);
    }
    int max = max_heap->array[0];
    int last = max_heap->array[max_heap->insert_index-1];
    max_heap->array[0] = last;
    max_heap->size--;
    max_heap->insert_index--;
    heapify_down(max_heap);
    return max;
};

void print_max_heap(struct heap *max_heap) {
    printf("[ ");
    for (int i = 0; i < max_heap->insert_index; i++) {
        printf("%d ", max_heap->array[i]);
    }
    printf(" ]\n");
};

int main() {
    struct heap *max_heap = create_max_heap(10);
    insert(max_heap, 10);
    insert(max_heap, 20);
    insert(max_heap, 15);
    insert(max_heap, 30);
    insert(max_heap, 25);
    print_max_heap(max_heap);
    return 0;
};