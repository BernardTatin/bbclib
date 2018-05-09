/*
 * _standard.h
 * generated by noweb
 */
#ifndef INCLUDE__COMPAT__STANDARD_H_
#define INCLUDE__COMPAT__STANDARD_H_

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#if defined(__WATCOMC__)
#define no_c11
#define with_watcominline
#elif defined(_MSC_VER)
#define no_c11
#elif defined(__TURBOC__)
#define no_c11
#endif

#ifndef no_c11
  #include <stdbool.h>
  #include <stdint.h>
#else
typedef enum {
        false = 0,
        true = 1
} bool;

typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef long int32_t;
typedef unsigned long uint32_t;

typedef unsigned int size_t;

#ifndef no_inline
  #define no_inline
#endif
#endif

#if defined(with_watcominline)
        #define INLINE __inline
#elif !defined(no_inline)
        #define INLINE inline
#else
        #define INLINE
#endif

#if defined(__with_irqs)
  #define VOLATILE volatile
#else
  #define VOLATILE
#endif


#if !defined(INT)
#define INT int
#endif

#endif /* INCLUDE__COMPAT__STANDARD_H_ */