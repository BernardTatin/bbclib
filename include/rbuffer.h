/*
 * File:   rbuffer.h
 * Author: BernardT
 *
 * Created on 19 mai 2014, 11:56
 */

#ifndef RBUFFER_H
#    define	RBUFFER_H

#    define _RBUBBER_BITS	8
#    define RBUFFER_SIZE	(1 << _RBUBBER_BITS)
#    define RBUFFER_MASK	(RBUFFER_SIZE - 1)

typedef struct {
	volatile char buffer[RBUFFER_SIZE + 1];
	volatile int in;
	volatile int out;
	volatile int line_count;
	volatile int overrun;
} TSrbuffer;

static inline void rbf_reset(TSrbuffer *rb) {
	memset(rb, 0, sizeof (TSrbuffer));
}

static inline bool rbf_has_lines(TSrbuffer *rb) {
	int lc = rb->line_count;
	return lc != 0;
}

static inline int rbf_on_overrun(TSrbuffer *rb) {
	int ovr = rb->overrun;
	ovr++;
	rb->overrun = ovr;
	return ovr;
}

static inline void rbf_add_char(TSrbuffer *rb, const char c) {
	if (c != '\r') {
		int in = rb->in;

		rb->buffer[in++] = c;
		in &= RBUFFER_MASK;
		rb->in = in;
		if (c == '\n') {
			rb->line_count++;
		}
	}
}

static inline void rbf_end_of_line(TSrbuffer *rb) {
	int in = rb->in;

	rb->buffer[in] = 0;
	rb->line_count++;
}

static inline char rbf_get_char(TSrbuffer *rb) {
	int out = rb->out;
	char c = rb->buffer[out++];
	out &= RBUFFER_MASK;
	rb->out = out;
	if (c == '\n' && rb->line_count) {
		rb->line_count--;
	}
	return c;
}

static inline bool rbf_has_chars(TSrbuffer *rb) {
	return rb->in != rb->out;
}

int rbf_add_line(TSrbuffer *rb, char *line);
int rbf_get_line(TSrbuffer *rb, char *line);
#endif	/* RBUFFER_H */

