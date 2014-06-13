/**
 * @file   rbuffer-add-line.c
 * @author BernardT
 *
 * @date 19 mai 2014, 11:56
 */


#include <string.h>
#if !defined(_MSC_VER)
#include <stdbool.h>
#endif

#include "rbuffer.h"

void rbf_add_line(TSrbuffer *rb, char *line) {
        char c;

        while ((c = *(line++)) != 0) {
                rbf_add_char(rb, c);
        }
        rbf_end_of_line(rb);
}
