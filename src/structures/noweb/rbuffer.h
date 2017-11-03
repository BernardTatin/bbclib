#define _RBUFFER_BITS   8
#define RBUFFER_SIZE    (1 << _RBUFFER_BITS)
#define RBUFFER_MASK    (RBUFFER_SIZE - 1)

#if defined(__with_irqs)
  #define VOLATILE volatile
#else
  #define VOLATILE
#endif

/**
 * @struct TSrbuffer
 * La structure gérant le buffer tournant.
 */
typedef struct {
    VOLATILE int in;
    VOLATILE int out;
    VOLATILE int line_count;
    VOLATILE char buffer[RBUFFER_SIZE];
} TSrbuffer;
static INLINE void rbf_add_char(TSrbuffer *rb, const char c) {
    if (c != '\r') {
        rb->buffer[rb->in++] = c;
        rb->in &= RBUFFER_MASK;
        if (c == '\n') {
            rb->line_count++;
        }
    }
}


