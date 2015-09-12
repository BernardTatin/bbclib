/*
 * svstack.h
 *
 *  Created on: 12 sept. 2015
 *      Author: bernard
 */

#ifndef STRUCTURES_SVSTACK_H_
#define STRUCTURES_SVSTACK_H_

#include "svariant.h"

typedef struct _SVStack {
    size_t size;
    size_t stack_ptr;
    pSVariant *stack;
} SVStack;

static inline SVStack *new_svstack(size_t size) {
    SVStack *stack = (SVStack *) calloc(1, sizeof(SVStack));
    stack->size = size;
    stack->stack_ptr = 0;
    stack->stack = (pSVariant *) calloc(size, sizeof(pSVariant));
    return stack;
}

static inline bool is_svstack_empty(SVStack *stack) {
    return stack->stack_ptr == 0;
}

static inline bool is_svstack_full(SVStack *stack) {
    return stack->stack_ptr >= stack->size;
}

static inline bool sv_push(SVStack *stack, SVariant *value) {
    if (!is_svstack_full(stack)) {
        stack->stack[stack->stack_ptr] = value;
        stack->stack_ptr++;
        return true;
    } else {
        return false;
    }
}

static inline SVariant *sv_pop(SVStack *stack) {
    if (!is_svstack_empty(stack)) {
        stack->stack_ptr--;
        return stack->stack[stack->stack_ptr];
    } else {
        return NULL;
    }
}


#endif /* STRUCTURES_SVSTACK_H_ */
