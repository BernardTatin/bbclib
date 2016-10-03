/*
 * squeue.h
 *
 *  Created on: 2 sept. 2015
 *      Author: bernard
 */

#ifndef STRUCTURES_SQUEUE_H_
#define STRUCTURES_SQUEUE_H_

typedef struct _sq_element {
    void *value;
    struct _sq_element *next;
} sq_element;

static INLINE sq_element *sq_new_element(void *value) {
    sq_element *elt = (sq_element *) calloc(1, sizeof(sq_element));
    elt->value = value;
    return elt;
}

static INLINE void sq_delete_element(sq_element *elt) {
    if (elt != NULL) {
        free(elt);
    }
}

static INLINE void sq_set_next(sq_element *elt, sq_element *next) {
    elt->next = next;
}

typedef struct _sq_queue {
    sq_element *_input;
    sq_element *_output;
} sq_queue;

static INLINE sq_queue *sq_new_queue(void) {
    return (sq_queue *) calloc(1, sizeof(sq_queue));
}

static INLINE bool sq_isempty(sq_queue *queue) {
    return queue->_input == NULL || queue->_output == NULL;
}

void sq_inner_push(sq_queue *queue, sq_element *elt);
sq_element *sq_inner_pop(sq_queue *queue);

static INLINE void sq_push(sq_queue *queue, void *value) {
    sq_inner_push(queue, sq_new_element(value));
}

static INLINE void *sq_pop(sq_queue *queue) {
    sq_element *elt = sq_inner_pop(queue);
    if (elt != NULL) {
        void *r = elt->value;
        sq_delete_element(elt);
        return r;
    } else {
        return NULL;
    }
}
#endif /* STRUCTURES_SQUEUE_H_ */
