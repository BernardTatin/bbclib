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
        #include "_compat/_stdbool.h"
        #include "_compat/_stdint.h"
        #ifndef no_inline
                #define no_inline
        #endif
#endif

#include <string.h>

#ifndef no_inline
        #define INLINE inline
#else
        #define INLINE
#endif

#endif /* INCLUDE__COMPAT__STANDARD_H_ */
