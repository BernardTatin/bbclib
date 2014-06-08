/**
 * @file bb_printf.c
 * @author bbernard
 *
 * @date 27 mai 2014
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>


#include "bbclib.h"
#include "uart-foo.h"

#define _prbuffer_len   64

static char *_to_str(const uint32_t t, const char filler,
        const int len, const int base) {
    static char b[_prbuffer_len + 1];
    char *dst = b + _prbuffer_len - 1;
    int idx = 0;

    memset(b, filler, _prbuffer_len + 1);
    b[_prbuffer_len] = 0;

    if (t == 0) {
        *(dst--) = '0';
    } else {
        if (base == 16 || base == 2) {
            uint32_t x = (uint32_t) t;
			int dec = base == 16 ? 4 : 1;

            while (x != 0 && idx++ < _prbuffer_len) {
                int32_t r = (int32_t)(x & (base - 1));
                x >>= dec;
                if (r < 10) {
                    *(dst--) = '0' + r;
                } else {
                    *(dst--) = 'a' + r - 10;
                }
            }
        } else {
            bool neg = false;
            int32_t x = (int32_t) t;

            if (x < 0) {
                x = -x;
                neg = true;
            }
            while (x != 0 && idx++ < _prbuffer_len) {
                if (x < base) {
                    *(dst--) = '0' + x;
                    x = 0;
                } else {
                    int32_t r = x % base;
                    x /= base;
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

static inline char *hex_to_str(const uint32_t t, const char filler,
        const int len) {
    return _to_str(t, filler, len, 16);
}

static inline char *int_to_str(const uint32_t t, const char filler,
        const int len) {
    return _to_str(t, filler, len, 10);
}

void debug_printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    char symbol;
    char filler = ' ';
    int dlen = -1;
    bool inpct = false;
    uint32_t value = 0;
    bool has_value = false;

    uart_wait_end_of_tx();
    while ((symbol = *(fmt++)) != 0) {
        if (symbol == '%') {
            symbol = *(fmt++);
            inpct = true;
            has_value = false;
            filler = ' ';
            dlen = -1;
        }
        if (inpct) {
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
                    value = va_arg(ap, uint32_t);
                    has_value = true;
                    break;

                }
                case 'd':
                {
                    if (!has_value) {
                        value = (uint32_t) va_arg(ap, int) & 0xffffl;
                    }
					rbf_add_line(&uart_tx_buffer, int_to_str(value, filler, dlen));
                    inpct = false;
                    break;
                }
                case 'b':
                    if (!has_value) {
                        value = (uint32_t) va_arg(ap, int) & 0xffffl;
                    }
					rbf_add_line(&uart_tx_buffer, _to_str(value, filler, dlen, 2));
                    inpct = false;
                    break;
                case 'x':
                    if (!has_value) {
                        value = (uint32_t) va_arg(ap, int) & 0xffffl;
                    }
					rbf_add_line(&uart_tx_buffer, hex_to_str(value, filler, dlen));
                    inpct = false;
                    break;
                case '0':
                    filler = '0';
                    break;
                case '1'...'9':
                    if (dlen == -1) {
                        dlen = symbol - '0';
                    } else {
                        dlen = dlen * 10 + (symbol - '0');
                    }
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

