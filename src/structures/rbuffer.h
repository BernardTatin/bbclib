/**
 * @file   rbuffer.h
 * @author BernardT
 *
 * @date 19 mai 2014, 11:56
 *
 * @section description description
 * Impl�mentation d'un buffer tournant capable de g�rer des lignes
 * d�limit�es par le caract�re LF ('\\n'). CR ('\\r') n'est pas pris en compte.
 */

#ifndef RBUFFER_H
#define RBUFFER_H

/**
 * @def _RBUFFER_BITS
 * La taille du tampon doit �tre une puissance de 2. _RBUFFER_BITS est ce nombre.
 *
 * @def RBUFFER_SIZE
 * La taille du tampon.
 *
 * @def RBUFFER_MASK
 * La taille du tampon d�cr�ment�e de 1.
 */
#define _RBUFFER_BITS   8
#define RBUFFER_SIZE    (1 << _RBUFFER_BITS)
#define RBUFFER_MASK    (RBUFFER_SIZE - 1)

/**
 * @struct TSrbuffer
 * La structure g�rant le buffer tournant.
 */
typedef struct {
    volatile int in; /**< index du caract�re � ajouter */
    volatile int out; /**< index du caract�re � sortir */
    volatile int line_count; /**< nombre de lignes contenues dans le tampon */
    volatile char buffer[RBUFFER_SIZE]; /**< le tampon */
} TSrbuffer;

/**
 * Remet � 0 le tampon
 * @param rb le tampon � r�initialiser
 */
static INLINE void rbf_reset(TSrbuffer *rb) {
    memset(rb, 0, sizeof (TSrbuffer));
}

/**
 * D�termine si le tampon contient des lignes
 * @param rb le tampon � tester
 * @return true il y a des lignes dans le tampon,
 * @return false il n'y a pas de lignes dans le tampon.
 */
static INLINE bool rbf_has_lines(TSrbuffer *rb) {
    int lc = rb->line_count;
    return lc != 0;
}

/**
 * Ajoute un caract�re au tampon si ce caract�re est diff�rent de CR ('\\r')
 * @param rb le tampon � modifier
 * @param c la caraact�re � placer
 */
static INLINE void rbf_add_char(TSrbuffer *rb, const char c) {
    if (c != '\r') {
        rb->buffer[rb->in++] = c;
        rb->in &= RBUFFER_MASK;
        if (c == '\n') {
            rb->line_count++;
        }
    }
}

/**
 * Cr�e une fin de ligne au tampon, <em>i.e.</em> place un '\0' dans le tampon
 * et incr�mente le num�ro de ligne.
 * @param rb le tampon � modifier.
 */
static INLINE void rbf_end_of_line(TSrbuffer *rb) {
    rb->buffer[rb->in] = 0;
    rb->line_count++;
}

/**
 * Lit un caract�re dans le tampon, <em>i.e.</em> retourne le caract�re point� par
 * <code>rb->out</code>.
 * @param rb le tampon � examiner
 * @return le caract�re lu.
 */
static INLINE char rbf_get_char(TSrbuffer *rb) {
    int out = rb->out;
    char c = rb->buffer[out++];
    out &= RBUFFER_MASK;
    rb->out = out;
    if (c == '\n' && rb->line_count) {
        rb->line_count--;
    }
    return c;
}

/**
 * Y a t-il des caract�res disponibles dans le tampon.
 *
 * @param rb le tampon � examiner,
 * @return true il y a des caract�res
 * @return false il n'y a pas de caract�res.
 */
static INLINE bool rbf_has_chars(TSrbuffer *rb) {
    return rb->in != rb->out;
}
/**
 * A joute une ligne au tampon, <em>i.e.</em> une cha�ne C.
 * @param rb le tampon � modifier,
 * @param line la ligne � ajouter
 */
void rbf_add_line(TSrbuffer *rb, char *line);

/**
 * Lit une ligne dans le tampon.
 * @param rb le tampon � examiner et modifier
 * @param line la cha�ne � remplir
 * @return le nombre de caract�res plac�s dans la ligne
 */
int rbf_get_line(TSrbuffer *rb, char *line);
#endif  /* RBUFFER_H */

