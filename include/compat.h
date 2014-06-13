/**
 * compat.h
 */

#if !defined(__compat_h__)
#define __compat_h__

#include <stdlib.h>
#include <stdarg.h>
#if !defined(_MSC_VER)
#include <stdbool.h>
#include <stdint.h>
#endif

#if defined(_MSC_VER)
typedef enum {false = 0, true = 1 } bool;
typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef long int32_t;
typedef unsigned long uint32_t;
#endif

#if defined(__WATCOMC__)
#define INLINE inline
#elif defined(_MSC_VER)
#define INLINE
#else
#define INLINE inline
#endif


#endif
