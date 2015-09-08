/*
 * test_stack.c
 *
 *  Created on: 9 sept. 2015
 *      Author: bernard
 */

#include <stdio.h>

#include "bbclib.h"
#include "aistack.h"
#include "tests.h"

static const int STACK_SIZE = 512;
static const int loops = 300;

int test_stack(void) {
    int i;
    int errors = 0;
    TSStack *stack = new_stack(STACK_SIZE);

    fprintf(stdout, "TEST STACK ...\n");
    for (i=0; i<loops; i++) {
        ais_push(stack, i);
    }
    for (i=0; i<loops; i++) {
        int_stack v = ais_pop(stack);
        int_stack expected = (int_stack)(loops - i - 1);

        if (v != expected) {
            fprintf(stderr, "-> failure [%3d], expected %3d, get %3d\n",
                    i, expected, v);
            errors++;
#if 0
        } else {
            fprintf(stderr, ".. failure [%3d], expected %3d, get %3d\n",
                    i, expected, v);
#endif
        }
    }
    fprintf(stdout, "TEST STACK : %d errors\n", errors);
    return errors;
}

