/*
 * _standard.h
 *
 *  Created on: 15 oct. 2014
 *      Author: bernard
 */

#ifndef INCLUDE__COMPAT__STANDARD_H_
#define INCLUDE__COMPAT__STANDARD_H_

#include <stdlib.h>
#include <stdarg.h>
#ifndef no_c11
#include <stdbool.h>
#include <stdint.h>
#else
typedef enum {
        false = 0, true = 1} bool;
typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef long int32_t;
typedef unsigned long uint32_t;
#endif
#include <string.h>

#ifndef no_inline
#define INLINE inline
#else
#define INLINE
#endif

#endif /* INCLUDE__COMPAT__STANDARD_H_ */
