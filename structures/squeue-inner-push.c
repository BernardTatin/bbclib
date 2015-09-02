/*
 * squeue-inner-push.c
 *
 *  Created on: 2 sept. 2015
 *      Author: bernard
 */

#include "squeue.h"

void sq_inner_push(sq_queue *queue, sq_element *elt) {
    if (sq_isempty(queue)) {
        queue->_input = elt;
        queue->_output = elt;
    } else {
        sq_set_next(queue->_input, elt);
        queue->_input = elt;
    }
}

