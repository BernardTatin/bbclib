/*
 * aistack.h
 *
 *  Created on: 9 sept. 2015
 *      Author: bernard
 */

#ifndef STRUCTURES_AISTACK_H_
#define STRUCTURES_AISTACK_H_

typedef int int_stack;

typedef struct _TSStack {
    size_t size;
    size_t stack_ptr;
    int_stack *stack;
} TSStack;

static inline TSStack *new_stack(size_t size) {
    TSStack *stack = (TSStack *) calloc(1, sizeof(TSStack));
    stack->size = size;
    stack->stack_ptr = 0;
    stack->stack = (int_stack *) calloc(size, sizeof(int_stack));
    return stack;
}

static inline bool is_stack_empty(TSStack *stack) {
    return stack->stack_ptr == 0;
}

static inline bool is_stack_full(TSStack *stack) {
    return stack->stack_ptr >= stack->size;
}

static inline bool ais_push(TSStack *stack, int_stack value) {
    if (!is_stack_full(stack)) {
        stack->stack[stack->stack_ptr] = value;
        stack->stack_ptr++;
        return true;
    } else {
        return false;
    }
}

static inline int_stack ais_pop(TSStack *stack) {
    if (!is_stack_empty(stack)) {
        stack->stack_ptr--;
        return stack->stack[stack->stack_ptr];
    } else {
        return (int_stack) -1;
    }
}

#endif /* STRUCTURES_AISTACK_H_ */
