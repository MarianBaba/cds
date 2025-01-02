#include<stdlib.h>

struct node {
    int index;
    struct node *next;
};

struct list {
    struct node *root;
    int len;
};

void add_node(struct list *l, int k) {
    struct node *n = malloc(sizeof(struct node));
    n->index = k;
    n->next = l->root;
    l->root = n;
    l->len++;
}

struct node *find_all_indices(int *array, int len, int target) {
    struct list *l = malloc(sizeof(struct list));
    for (int i = 0; i < len; i++) {
        if (array[i] == target) {
            add_node(l, i);
        }
    }
    return l->root;
}