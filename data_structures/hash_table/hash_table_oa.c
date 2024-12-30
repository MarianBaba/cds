#include <stdio.h>
#include <stdlib.h>

#define EMPTY -1
#define DELETED -2

struct hash_table {
    int *array;
    int size;
};

// Primary hash function
int h1(int key, int m) {
    return key % m;
}

// Secondary hash function
int h2(int key, int m) {
    return 1 + (key % (m - 1));
}

// Combined hash function
int hash(int key, int i, int m) {
    return (h1(key, m) + i * h2(key, m)) % m;
}

// Create and initialize the hash table
struct hash_table *create_hash_table(int size) {
    struct hash_table *table = malloc(sizeof(struct hash_table));
    table->array = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        table->array[i] = EMPTY; // Initialize all slots as empty
    }
    table->size = size;
    return table;
}

// Insert a key into the hash table
void insert(struct hash_table *table, int data) {
    for (int i = 0; i < table->size; i++) {
        int hash_code = hash(data, i, table->size);
        if (table->array[hash_code] == EMPTY || table->array[hash_code] == DELETED) {
            table->array[hash_code] = data;
            return;
        }
    }
    printf("Error: Hash table is full. Cannot insert %d\n", data);
}

// Lookup a key in the hash table
int lookup(struct hash_table *table, int key) {
    for (int i = 0; i < table->size; i++) {
        int hash_code = hash(key, i, table->size);
        if (table->array[hash_code] == EMPTY) {
            return -1; // Key not found
        }
        if (table->array[hash_code] == key) {
            return hash_code; // Key found
        }
    }
    return -1; // Key not found after full probing
}

// Delete a key from the hash table
void delete(struct hash_table *table, int key) {
    for (int i = 0; i < table->size; i++) {
        int hash_code = hash(key, i, table->size);
        if (table->array[hash_code] == key) {
            table->array[hash_code] = DELETED; // Mark slot as deleted
            return;
        }
        if (table->array[hash_code] == EMPTY) {
            printf("Error: Key %d not found\n", key);
            return;
        }
    }
    printf("Error: Key %d not found\n", key);
}

int main() {
    struct hash_table *table = create_hash_table(7); // Use a prime number for size
    insert(table, 30);
    insert(table, 300);
    insert(table, 2);
    insert(table, 0);
    insert(table, 1000);

    if (lookup(table, 30) != -1) printf("30 found\n");
    if (lookup(table, 300) != -1) printf("300 found\n");
    if (lookup(table, 2) != -1) printf("2 found\n");
    if (lookup(table, 0) != -1) printf("0 found\n");
    if (lookup(table, 1000) != -1) printf("1000 found\n");

    delete(table, 300);
    if (lookup(table, 300) == -1) printf("300 deleted\n");

    return 0;
}