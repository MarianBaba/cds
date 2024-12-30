// hash table implementation with chained hashing: 
// the hash table contains cells with a pointer to a linked list

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct hash_table {
    struct node **cells;
    int size;
};

// Define the hash function using the multiplication method
unsigned int hash(int key, int table_size) {
    const double A = 0.618033;
    double fractional_part = key * A - floor(key * A);
    unsigned int hash = (unsigned int)(floor(table_size * fractional_part));
    return hash;
}

struct hash_table *create_hash_table(int size) {
    struct hash_table *table = malloc(sizeof(struct hash_table));
    table->size = size;
    table->cells = malloc(sizeof(struct node) * size);
    return table;
}

struct node *create_node(int data) {
    struct node *new = malloc(sizeof(struct node));
    new->data = data;
    new->next = NULL;
    return new;
}

void insert(struct hash_table *table, int data) {
    int hash_code = hash(data, table->size);
    struct node *current_head = table->cells[hash_code];
    struct node *new = create_node(data);
    new->next = current_head;
    table->cells[hash_code] = new;
}

struct node *lookup(struct hash_table *table, int key) {
    int hash_code = hash(key, table->size);
    struct node *head = table->cells[hash_code];
    struct node *found = NULL;
    while (head != NULL) {
        if (head->data == key) {
            found = head;
            break;
        }
        head = head->next;
    }
    return found;
} 


int main() {
    struct hash_table *table = create_hash_table(30);
    for (int i = 1; i <= 30; i++) {
        insert(table, i);
    }

    for (int i = 1; i <= 30; i++) {
        struct node *n = lookup(table, i);
        if (n == NULL) {
            printf("%d not found\n", i);
        } else {
            printf("%d found\n", n->data);
        }
    }

    struct node *node = lookup(table, 1000);
    if (node == NULL) {
        printf("1000 not found");
    }

    return 0;
};