/**
 * @file uart-foo.c
 * @author bbernard
 *
 * @date 8 Juin 2014
 */

#include <stdio.h>
#include <stdarg.h>

#include "include/bbclib.h"
#include "include/uart-foo.h"

TSrbuffer uart_tx_buffer;

void uart_start_printf(void) {
    char c;
    while (rbf_has_chars(&uart_tx_buffer)) {
        c = rbf_get_char(&uart_tx_buffer);
        putchar(c);
    }
}

