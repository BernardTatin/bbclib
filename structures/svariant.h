/*
 * svariant.h
 *
 *  Created on: 12 sept. 2015
 *      Author: bernard
 */

#ifndef STRUCTURES_SVARIANT_H_
#define STRUCTURES_SVARIANT_H_

typedef enum {
    sv_int,
    sv_float,
    sv_double,
    sv_char,
    sv_string
} SVariantType;

typedef struct _SVariant {
    int size;               /* if size > 1, it's an array! */
    SVariantType type;
    void *value;
} SVariant;

typedef SVariant *pSVariant;

static inline SVariant *_sv_new(void) {
    return (SVariant *)calloc(1, sizeof(SVariant));
}

#define _SVMAKER(vtype, value) \
static inline SVariant *sv_new_ ## vtype(vtype value) { \
    SVariant *sv = _sv_new(); \
    vtype *nvalue = (vtype *)malloc(sizeof(vtype)); \
 \
    *nvalue = value; \
    sv->size = 1; \
    sv->type = sv_ ## vtype; \
    sv->value = nvalue; \
    return sv; \
}

_SVMAKER(int, value)
_SVMAKER(float, value)
_SVMAKER(double, value)
_SVMAKER(char, value)

#endif /* STRUCTURES_SVARIANT_H_ */
