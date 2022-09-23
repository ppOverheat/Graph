#include "stack.h"

struct stack* getTopValue(struct stack* top, double* last) {
    if (stackCount(top) > 0) {
        *last = top->value;
        top = pop(top);
    }
    return top;
}

int stackCount(struct stack* top) {//
    int count = 0;
    if (top != NULL) {
        top = top->next;
        count++;
    }
    return count;
}

struct stack* init(char operand, double value) {
    struct stack *tmp = (struct stack*) malloc(sizeof(struct stack));
    tmp->operand = operand;
    tmp->value = value;
    tmp->next = NULL;
    return tmp;
}

struct stack* push(char operand, double value, struct stack* top) {
    if (top == NULL) {
        top = init(operand, value);
    } else {
    struct stack *tmp = malloc(sizeof(struct stack));
    tmp->operand = operand;
    tmp->value = value;
    tmp->next = top;
    top = tmp;
    }
    return top;
}

struct stack* pop(struct stack* top) {
    if (top != NULL) {
        struct stack *tmp = top;
        top = top->next;
        free(tmp);
    }
    return top;
}

void destroy(struct stack* top) {
    while (top != NULL) {
        struct stack *p = top;
        top = top->next;
        free(p);
    }
}
