/**
 * @file test_bbprintf.c
 * @author bbernard
 *
 * @date 27 mai 2014
 */

#include <stdio.h>

#include "bbclib.h"
#include "tests.h"


void bbprintf_test(void) {
    debug_printf("debug_printf : Hey! Ca marche\n");
	for (int i=0; i<66000; i++) {
        debug_printf("i = %d, %5d, %05d, %x, %5x, %05x\n",
                     i, i, i, i, i, i);
    }
}

void bbprintf_reference(void) {
    printf("printf : Hey! Ca marche\n");
	for (int i=0; i<66000; i++) {
        printf("i = %d, %5d, %05d, %x, %5x, %05x\n",
                     i, i, i, i, i, i);
    }
}
