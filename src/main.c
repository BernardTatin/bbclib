/**
 * @file main.c
 * @author bbernard
 *
 * @date 27 mai 2014
 */

#include <stdio.h>

#include "bbclib.h"
#include "tests.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "%s --test|--ref|--bin\n", argv[0]);
        return EXIT_FAILURE;
    } else if (strcmp(argv[1], "--bin") == 0) {
		bbprintf_btest();
    } else if (strcmp(argv[1], "--test") == 0) {
		bbprintf_test();
    } else if (strcmp(argv[1], "--ref") == 0) {
        bbprintf_reference();
    } else if (strcmp(argv[1], "--queue") == 0) {
    	if (test_queue() != 0) {
    		return EXIT_FAILURE;
    	}
    } else {
        fprintf(stderr, "%s --test|--ref\n", argv[0]);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
