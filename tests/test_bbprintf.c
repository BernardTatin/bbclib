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
	for (int i=0; i<5; i++) {
        debug_printf("i = %d, %3d, %03d, %x, %3x, %03x\n",
                     i, i, i, i, i, i);
    }
}

void bbprintf_reference(void) {
    printf("printf : Hey! Ca marche\n");
	for (int i=0; i<5; i++) {
        printf("i = %d, %3d, %03d, %x, %3x, %03x\n",
                     i, i, i, i, i, i);
    }
}
