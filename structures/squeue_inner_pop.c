/*
 * squeue-inner-pop.c
 *
 *  Created on: 2 sept. 2015
 *      Author: bernard
 */

#include "bbclib.h"
#include "squeue.h"

sq_element *sq_inner_pop(sq_queue *queue) {
    if (sq_isempty(queue)) {
        return NULL;
    } else {
        sq_element *prt = queue->_output;
        queue->_output = queue->_output->next;
        if (queue->_output == NULL) {
            queue->_input = NULL;
        }
        return prt;
    }
}

