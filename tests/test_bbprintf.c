/**
 * @file test_bbprintf.c
 * @author bbernard
 *
 * @date 27 mai 2014
 *
 * @section description description
 *
 */

#include <stdio.h>

#include "bbclib.h"
#include "tests.h"

static const int32_t _nb_loops = 65536;

void bbprintf_btest(void) {
    int32_t i, j;

    for (j = 0; j < 0x0100; j++) {
        for (i = 0; i < 256; i++) {
            debug_printf("i = %d, %5d, %05d, %x, %5x, %05x, %016b\n", i, i, i,
                    i, i, i, i);
        }
    }
}

void bbprintf_test(void) {
    int32_t i;

    for (i = 0; i < _nb_loops; i++) {
        debug_printf("i = %d, %5d, %05d, %x, %5x, %016x\n", i, i, i, i, i, i);
    }
}

void bbprintf_reference(void) {
    int32_t i;

    for (i = 0; i < _nb_loops; i++) {
        printf("i = %d, %5d, %05d, %x, %5x, %016x\n", i, i, i, i, i, i);
    }
}
