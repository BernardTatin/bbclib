/**
 * @file   rbuffer-add-line.c
 * @author BernardT
 *
 * @date 19 mai 2014, 11:56
 */

#include "bbclib.h"

void rbf_add_line(TSrbuffer *rb, char *line) {
    char c;

    while ((c = *(line++)) != 0) {
        rbf_add_char(rb, c);
    }
    rbf_end_of_line(rb);
}
