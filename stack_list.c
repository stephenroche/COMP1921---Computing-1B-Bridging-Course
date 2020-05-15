#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct list_node list_node;
struct list_node {
    int       data;
    list_node *next;
};

struct stack {
    list_node   *top;
};

// create a new stack
stack_t create(void) {
    struct stack *s = malloc(sizeof *s);
    if (s == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    s->top = NULL;
    return s;
}

// add new item to stack
void push(stack_t stack, int item) {
    struct list_node *n = malloc(sizeof *n);
    n->data = item;
    n->next  = stack->top;
    stack->top = n;
}

// remove top item from stack and return it
int pop(stack_t stack) {
    int i;
    struct list_node *n;
    if (is_empty(stack)) {
        fprintf(stderr, "pop() of empty stack\n");
        exit(1);
    }
    n = stack->top;
    i = n->data;
    stack->top = stack->top->next;
    free(n);
    return i;
}

// return true if stack is empty
int is_empty(stack_t stack) {
    return stack->top == NULL;
}

// return top item from stack but don't remove it
int top(stack_t stack) {
    if (is_empty(stack)) {
        fprintf(stderr, "top() of empty stack\n");
        exit(1);
    }
    return stack->top->data;
}

// return number elements in stack
int size(stack_t stack) {
    int i = 0;
    struct list_node *n = stack->top;
    while (n != NULL) {
        i++;
        n = n->next;
    }
    return i;
}

// free a stack
void destroy(stack_t stack) {
    while (!is_empty(stack)) {
        pop(stack);
    }
    free(stack);
}
