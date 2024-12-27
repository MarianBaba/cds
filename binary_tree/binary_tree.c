#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *parent;
    struct node *right;
    struct node *left;
};

struct binary_tree {
    struct node *root;
};

struct binary_tree *create_bt() {
    struct binary_tree *bt = malloc(sizeof(struct binary_tree));
    if (bt == NULL) {
        printf("error allocating memory for new binary tree, exiting...\n");
        exit(1);
    }
    bt->root = NULL;
    return bt;
};


int main() {
    struct binary_tree *bt = create_bt();
    return 0;
};