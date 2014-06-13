/**
 * @file bb_printf.c
 * @author bbernard
 *
 * @date 27 mai 2014
 */

#include "compat.h"

#include "bbclib.h"
#include "uart-foo.h"

#define _prbuffer_len   32

// globals to spare stack usage.
static char _format_filler = ' ';
static int _format_len = -1;
static char _int_buffer[_prbuffer_len + 1];
static uint32_t _format_value = 0;
static bool _format_has_value = false;

static char *_to_str(const uint32_t t, const int base) {
    char *dst = _int_buffer + _prbuffer_len - 1;
    int idx = 0;

    memset(_int_buffer, _format_filler, _prbuffer_len + 1);
    _int_buffer[_prbuffer_len] = 0;

    if (t == 0) {
        *(dst--) = '0';
    } else {
        if (base == 16 || base == 2) {
            uint32_t x = (uint32_t) t;
                        int dec = base == 16 ? 4 : 1;

            while (x != 0 && idx++ < _prbuffer_len) {
                uint32_t r = x & ((uint32_t)base - 1);
                x >>= dec;
                if (r < 10) {
                    *(dst--) = '0' + (char)r;
                } else {
                    *(dst--) = 'a' + (char)(r - 10);
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
                    *(dst--) = '0' + (char)x;
                    x = 0;
                } else {
                    int32_t r = x % base;
                    x /= base;
                    *(dst--) = '0' + (char)r;
                }
            }
            if (neg) {
                *dst = '-';
            }
        }
    }
    if (_format_len == -1) {
            return dst + 1;
    } else {
        return _int_buffer + _prbuffer_len - _format_len;
    }
}

static inline char *hex_to_str(const uint32_t t) {
    return _to_str(t, 16);
}

static inline char *bin_to_str(const uint32_t t) {
    return _to_str(t, 16);
}

static inline char *int_to_str(const uint32_t t) {
    return _to_str(t, 10);
}


void debug_printf(const char *fmt, ...) {
    va_list ap;
    char symbol;
    bool inpct = false;

#define _get_int16_value()    if (!_format_has_value) _format_value = (uint32_t) va_arg(ap, int) & 0xffffl

    va_start(ap, fmt);
    uart_wait_end_of_tx();
    while ((symbol = *(fmt++)) != 0) {
        if (symbol == '%') {
            symbol = *(fmt++);
            inpct = true;
            _format_has_value = false;
            _format_filler = ' ';
            _format_len = -1;
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
                    _format_value = va_arg(ap, uint32_t);
                    _format_has_value = true;
                    break;

                }
                case 'd':
                {
                    _get_int16_value();
                                        rbf_add_line(&uart_tx_buffer, int_to_str(_format_value));
                    inpct = false;
                    break;
                }
                case 'b':
                    _get_int16_value();
                                        rbf_add_line(&uart_tx_buffer, bin_to_str(_format_value));
                    inpct = false;
                    break;
                case 'x':
                    _get_int16_value();
                                        rbf_add_line(&uart_tx_buffer, hex_to_str(_format_value));
                    inpct = false;
                    break;
                case '0':
                    _format_filler = '0';
                    break;
                                case '1':
                                case '2':
                                case '3':
                                case '4':
                                case '5':
                                case '6':
                                case '7':
                                case '8':
                                case '9':
                    if (_format_len == -1) {
                        _format_len = symbol - '0';
                    } else {
                        _format_len = _format_len * 10 + (symbol - '0');
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

