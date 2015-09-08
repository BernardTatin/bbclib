/** 
 * @file   rbuffer-get-line.c
 * @author TATIN_B
 *
 * @date 4 juin 2014, 11:10
 */

#include "bbclib.h"

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
