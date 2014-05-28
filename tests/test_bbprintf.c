/**
 * @file test_bbprintf.c
 * @author bbernard
 *
 * @date 27 mai 2014
 */

#include <stdio.h>

#include "bbclib.h"
#include "tests.h"

const int _nb_loops = 65540;

void bbprintf_test(void) {
    debug_printf("debug_printf : Hey! Ca marche\n");
	for (int i=0; i<_nb_loops; i++) {
        debug_printf("i = %d, %5d, %05d, %x, %5x, %05x\n",
                     i, i, i, i, i, i);
    }
}

void bbprintf_reference(void) {
    printf("printf : Hey! Ca marche\n");
	for (int i=0; i<_nb_loops; i++) {
        printf("i = %d, %5d, %05d, %x, %5x, %05x\n",
                     i, i, i, i, i, i);
    }
}
