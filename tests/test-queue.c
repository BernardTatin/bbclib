/*
 * test-queue.c
 *
 *  Created on: 2 sept. 2015
 *      Author: bernard
 */

#include <stdio.h>

#include "bbclib.h"
#include "squeue.h"
#include "tests.h"

static const int NUMBER_OF_VALUES = 256;

int test_queue(void) {
    int i;
    int errors = 0;

    fprintf(stdout, "Test QUEUE ...\n");
    sq_queue *queue = sq_new_queue();
    for (i = 0; i < NUMBER_OF_VALUES; i++) {
        int *iptr = (int *) malloc(sizeof(int));
        *iptr = i;
        sq_push(queue, iptr);
    }

    for (i = 0; i < NUMBER_OF_VALUES; i++) {
        int *iptr = (int *) sq_pop(queue);
        if (iptr != NULL) {
            if (*iptr != i) {
                fprintf(stderr, "queue[%d] != %d\n", i, *iptr);
                errors++;
            }
            free(iptr);
        } else {
            fprintf(stderr, "queue[%d] == NULL !!!\n", i);
            errors++;
        }
    }
    fprintf(stdout, "Test QUEUE : %d errors\n", errors);
    return errors;
}
