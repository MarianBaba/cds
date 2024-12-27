#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

struct queue {
    int length;
    struct node *head;
    struct node *tail;
};

int dequeue(struct queue *queue) {
    if (queue == NULL) {
        printf("queue is undefined, exiting...\n");
        exit(1);
    }
    if (queue->length == 0) {
        printf("queue is empty, underflow...\n");
        exit(1);
    }
    // get data to return
    int data = queue->head->data;

    struct node *tmp = queue->head;
    queue->head = queue->head->prev;

    //check if the queue is empty
    if (queue->head == NULL) {
        queue->tail = NULL;
    } else {
        queue->head->next = NULL;
    }
    free(tmp);
    queue->length--;
    return data;
};

void enqueue(struct queue *queue, int data) {
    if (queue == NULL) {
        printf("queue is undefinied, exiting...\n");
        exit(1);
    }
    struct node *new = malloc(sizeof(struct node));
    if (new == NULL) {
        printf("Error: Memory allocation failed, exiting...\n");
        exit(1);
    }
    new->data = data;
    if (queue->length == 0) {
        new->next = NULL;
        new->prev = NULL;
        queue->head = new;
        queue->tail = new;
    } else {
        new->next = queue->tail;
        new->prev = NULL;
        queue->tail->prev = new;
        queue->tail = new;
    }
    queue->length++;
};

struct queue *create_queue() {
    struct queue *queue = malloc(sizeof(struct queue));
    queue->head = NULL;
    queue->tail = NULL;
    queue->length = 0;
    return queue;
};

void print_queue(struct queue *queue) {
    struct node *current = queue->tail;
    while (current != NULL) {
        printf("[%d] -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
    return;
}

int main() {
    struct queue *queue = create_queue();
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    print_queue(queue);
    dequeue(queue);
    print_queue(queue);
    enqueue(queue, 10);
    print_queue(queue);
    return 0;
};