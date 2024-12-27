#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct stack {
    struct node *top;
};

int pop(struct stack *stack) {
    if (stack == NULL || stack->top == NULL) {
        printf("stack underflow, exiting...\n");
        exit(1);
    } 
    int data = stack->top->data;
    struct node *old_top = stack->top;
    stack->top = stack->top->next;
    free(old_top);
    return data;
}

void peek(struct stack *stack) {
    if (stack == NULL || stack->top == NULL) {
        printf("stack underflow, exiting...\n");
        exit(1);
    }
    printf("value at the top of the stack: %d\n", stack->top->data);
    return;
}

void push(struct stack *stack, int data) {
    struct node *new = malloc(sizeof(struct node));
    if (new == NULL) {
        printf("error allocating memory for new node, exiting...");
        exit(1);
    }
    new->data = data;
    new->next = stack->top;
    stack->top = new;
    return;
}

void print_stack(struct stack *stack) {
    printf("\n");
    struct node *top = stack->top;
    while(top != NULL) {
        printf("[\t%d\t]", top->data);
        top = top->next;
    };
    printf("\n");
};

struct stack *create_stack() {
    struct stack *stack = malloc(sizeof(struct stack));
    if (stack == NULL) {
        printf("error allocating memory for new stack, exiting...\n");
        exit(1);
    }
    stack->top = NULL;
    return stack;
}

int main() {
    struct stack *stack = create_stack();
    push(stack, 10);
    push(stack, 1);
    push(stack, 20);
    push(stack, 15);

    int data = pop(stack);
    printf("%d\n", data);

    free(stack);
    return 0;
}