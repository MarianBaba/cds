#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node *next;
};

struct linked_list {
    struct node *head;
};

void reverse(struct linked_list *ls) {
    struct node *prev = NULL;
    struct node *current = ls->head;
    while (current != NULL) {
        struct node *next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    ls->head = prev;
}

struct linked_list *create() {
    struct linked_list *ls = malloc(sizeof(struct linked_list));
    ls->head = NULL;
    return ls;
}

void add(struct linked_list *ls, int data) {
    struct node *n = malloc(sizeof(struct node));
    n->key = data;
    n->next = ls->head;
    ls->head = n;
}

void print(struct linked_list *ls) {
    struct node *node = ls->head;
    while (node != NULL) {
        printf("%d -> ", node->key);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    struct linked_list *ls = create();
    add(ls, 10);
    add(ls, 20);
    add(ls, 30);
    add(ls, 40);
    add(ls, 50);
    add(ls, 60);
    add(ls, 70);
    add(ls, 80);
    add(ls, 90);
    print(ls);
    reverse(ls);
    print(ls);
    return 0;
}