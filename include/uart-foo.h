/**
 * @file uart-foo.h
 * @author bbernard
 *
 * @date 8 Juin 2014
 */

#if !defined(__uart_foo_h__)
#define __uart_foo_h__

extern TSrbuffer uart_tx_buffer;

static INLINE void uart_wait_end_of_tx(void) {
}

void uart_start_printf(void);

#endif /* __uart_foo_h__ */

