#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void print_linked_list(struct node *head) {
    struct node *current = head;
    while (current != NULL) {
        printf("[ ");
        printf("%d", current->data);
        printf(" ] -> ");
        current = current->next;
    }
    printf("NULL\n");
}

struct node *add_node(struct node *head, int data) {
    struct node *new = malloc(sizeof(struct node));
    if (new == NULL) {
        printf("a memory allocation error occurred\n");
        return NULL;
    }
    new->data = data;
    new->next = NULL;


    if (head == NULL) {
        return new;
    }

    while (head->next != NULL) {
        head = head->next;
    }
    
    head->next = new;
    return head;
}

int main() {
    

    struct node *head = add_node(NULL, 1);
    add_node(head, 2);
    add_node(head, 3);

    print_linked_list(head);

    return 0;
}