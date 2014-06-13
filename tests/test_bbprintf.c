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

const int _nb_loops = 65540;

void bbprintf_btest(void) {
  int i, j;

    debug_printf("debug_printf : Hey! Ca marche\n");
    for (j=0; j<0x1000; j++) {
        for (i=0; i<256; i++) {
            debug_printf("i = %d, %5d, %05d, %x, %5x, %05x, %016b\n",
                     i, i, i, i, i, i, i);
        }
    }
}

void bbprintf_test(void) {
  int i;

    debug_printf("debug_printf : Hey! Ca marche\n");
        for (i=0; i<_nb_loops; i++) {
        debug_printf("i = %d, %5d, %05d, %x, %5x, %016x\n",
                     i, i, i, i, i, i);
    }
}

void bbprintf_reference(void) {
  int i;

    printf("printf : Hey! Ca marche\n");
        for (i=0; i<_nb_loops; i++) {
        printf("i = %d, %5d, %05d, %x, %5x, %016x\n",
                     i, i, i, i, i, i);
    }
}
