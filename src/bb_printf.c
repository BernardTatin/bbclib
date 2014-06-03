/**
 * @file bb_printf.c
 * @author bbernard
 *
 * @date 27 mai 2014
 */

#include <stdio.h>
#include <stdarg.h>

#include "bbclib.h"

TSrbuffer uart_tx_buffer;
#define _prbuffer_len   64

void uart_wait_end_of_tx(void) {
}

void uart_start_printf(void) {
    char c;
    while (rbf_has_chars(&uart_tx_buffer)) {
        c = rbf_get_char(&uart_tx_buffer);
        putchar(c);
    }
}

static char *_to_str(const long t, const char filler, const int len, const int base) {
    static char b[_prbuffer_len + 1];
    char *dst = &b[_prbuffer_len - 1];
    int idx = 0;

    memset(b, filler, _prbuffer_len);
    b[_prbuffer_len] = 0;

    if (t == 0) {
        *(dst--) = '0';
    } else {
        if (base == 16) {
            unsigned long x = (unsigned long) t;

            while (x != 0 && idx++ < _prbuffer_len) {
                int r = (int)(x & 0xf);
                x >>= 4;
                if (r < 10) {
                    *(dst--) = '0' + r;
                } else {
                    *(dst--) = 'a' + r - 10;
                }
            }
        } else if (base == 10) {
            bool neg = false;
            long x = (long) t;

            if (x < 0) {
                x = -x;
                neg = true;
            }
            while (x != 0 && idx++ < _prbuffer_len) {
                if (x < 10) {
                    *(dst--) = '0' + x;
                    x = 0;
                } else {
                    long r = x % 10;
                    x /= 10;
                    *(dst--) = '0' + r;
                }
            }
            if (neg) {
                *dst = '-';
            }
        }
    }
    if (len == -1) {
        return dst + 1;
    } else {
        return b + _prbuffer_len - len;
    }
}

static inline char *hex_to_str(const long t, const char filler, const int len) {
    return _to_str(t, filler, len, 16);
}

static inline char *int_to_str(const long t, const char filler, const int len) {
    return _to_str(t, filler, len, 10);
}


void debug_printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    char symbol;
    char filler = ' ';
    int dlen = -1;
    bool inpct = false;
    long value = 0;
    bool has_value = false;

    uart_wait_end_of_tx();
    while ((symbol = *(fmt++)) != 0) {
        if (symbol == '%') {
            // symbol = *(fmt++);
            inpct = true;
            has_value = false;
            filler = ' ';
            dlen = -1;
        } else if (inpct) {
            switch (symbol) {
                case 's':
                    {
                        char *str = va_arg(ap, char*);

                        rbf_add_line(&uart_tx_buffer, str);
                        inpct = false;
                        break;
                    }
                case 'l':
                    {
                        value = va_arg(ap, long);
                        has_value = true;
                        break;

                    }
                case 'D':
                case 'd':
                    {
                        if (!has_value) {
                            value = (long) va_arg(ap, int) & 0xffffl;
                        }
                        rbf_add_line(&uart_tx_buffer, int_to_str(value, filler, dlen));
                        inpct = false;
                        break;
                    }
                case 'X':
                case 'x':
                    if (!has_value) {
                        value = (long) va_arg(ap, int) & 0xffffl;
                    }
                    rbf_add_line(&uart_tx_buffer, hex_to_str(value, filler, dlen));
                    inpct = false;
                    break;
                case '0':
                    filler = '0';
                    break;
                case '1'...'9':
                    dlen = symbol - '0';
                    break;
            }
        } else {
            rbf_add_char(&uart_tx_buffer, symbol);
        }
    }
    rbf_end_of_line(&uart_tx_buffer);
    va_end(ap);
    uart_start_printf();
}
