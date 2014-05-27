/*
 * File:   rbuffer.c
 * Author: BernardT
 *
 * Created on 19 mai 2014, 11:56
 */


#include <string.h>
#include <stdbool.h>

#include "rbuffer.h"

int rbf_add_line(TSrbuffer *rb, char *line) {
	char c;
	int r = 0;

	while ((c = *(line++)) != 0) {
		rbf_add_char(rb, c);
		r++;
	}
	rbf_end_of_line(rb);
	return r;
}

int rbf_get_line(TSrbuffer *rb, char *line) {
	char c;
	int r = 0;

	while (rbf_has_chars(rb)) {
		c = rbf_get_char(rb);

		if (c == '\n') {
			break;
		}
        if (c != 0) {
            *(line++) = c;
        }
		r++;
	}
	*line = 0;
	return r;
}
