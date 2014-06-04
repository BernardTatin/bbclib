/**
 * @file   rbuffer.h
 * @author BernardT
 *
 * @date 19 mai 2014, 11:56
 *
 * @section description description
 * Implémentation d'un buffer tournant capable de gérer des lignes
 * délimitées par le caractère LF ('\\n'). CR ('\\r') n'est pas pris en compte.
 */

#ifndef RBUFFER_H
#define	RBUFFER_H

#include <string.h>

/**
 * @def _RBUBBER_BITS
 * La taille du tampon doit être une puissance de 2. _RBUBBER_BITS est ce nombre.
 *
 * @def RBUFFER_SIZE
 * La taille du tampon.
 *
 * @def RBUFFER_MASK
 * La taille du tampon décrémentée de 1.
 */
#define _RBUBBER_BITS	8
#define RBUFFER_SIZE	(1 << _RBUBBER_BITS)
#define RBUFFER_MASK	(RBUFFER_SIZE - 1)

/**
 * @struct TSrbuffer
 * La structure gérant le buffer tournant.
 */
typedef struct {
    volatile char buffer[RBUFFER_SIZE + 1];	/**< le tampon */
    volatile int in;						/**< index du caractère à ajouter */
    volatile int out;						/**< index du caractère à sortir */
    volatile int line_count;				/**< nombre de lignes contenues dans le tampon */
} TSrbuffer;

/**
 * Remet à 0 le tampon
 * @param rb le tampon à réinitialiser
 */
static inline void rbf_reset(TSrbuffer *rb) {
    memset(rb, 0, sizeof (TSrbuffer));
}

/**
 * Détermine si le tampon contient des lignes
 * @param rb le tampon à tester
 * @retval true il y a des lignes dans le tampon,
 * @retval false il n'y a pas de lignes dans le tampon.
 */
static inline bool rbf_has_lines(TSrbuffer *rb) {
    int lc = rb->line_count;
    return lc != 0;
}

/**
 * Ajoute un caractère au tampon si ce caractère est différent de CR ('\\r')
 * @param rb le tampon à modifier
 * @param c la caraactère à placer
 */
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

/**
 * Crée une fin de ligne au tampon, <em>i.e.</em> place un '\0' dans le tampon
 * et incrémente le numéro de ligne.
 * @param rb le tampon à modifier.
 */
static inline void rbf_end_of_line(TSrbuffer *rb) {
    int in = rb->in;

	rb->buffer[in] = 0;
    rb->line_count++;
}

/**
 * Lit un caractère dans le tampon, <em>i.e.</em> retourne le caractère pointé par
 * <code>rb->out</code>.
 * @param rb le tampon à examiner
 * @return le caractère lu.
 */
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

/**
 * Y a t-il des caractères disponibles dans le tampon.
 *
 * @param rb le tampon à examiner,
 * @retval true il y a des caractères
 * @retval false il n'y a pas de caractères.
 */
static inline bool rbf_has_chars(TSrbuffer *rb) {
    return rb->in != rb->out;
}
/**
 * A joute une ligne au tampon, <em>i.e.</em> une chaîne C.
 * @param rb le tampon à modifier,
 * @param line la ligne à ajouter
 * @return le nombre de caractères ajoutés
 */
int rbf_add_line(TSrbuffer *rb, char *line);

/**
 * Lit une ligne dans le tampon.
 * @param rb le tampon à examiner et modifier
 * @param line la chaîne à remplir
 * @return le nombre de caractères placés dans la ligne
 */
int rbf_get_line(TSrbuffer *rb, char *line);
#endif	/* RBUFFER_H */


