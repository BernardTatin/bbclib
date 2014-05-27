/**
 * @file test_bbprintf.c
 * @author bbernard
 *
 * @date 27 mai 2014
 */

#include "bbclib.h"

int main(int argc, char **argv) {
    int i;

    debug_printf("Hey! Ca marche\n");
	for (i=0; i<5; i++) {
        debug_printf("i = %d, %3d, %03d, %x, %3x, %03x\n",
                     i, i, i, i, i, i);
    }
    return EXIT_SUCCESS;
}
