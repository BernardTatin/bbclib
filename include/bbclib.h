/**
 * @file bbclib.h
 * @author bbernard
 *
 * @date 27 mai 2014
 */

 #if !defined(__bbclib_h__)
 #define __bbclib_h__

#include <stdlib.h>
#if !defined(_MSC_VER)
#include <stdint.h>
#include <stdbool.h>
#endif
#include <string.h>

#include "structures/rbuffer.h"

void debug_printf(const char *fmt, ...);

 #endif /* __bbclib_h__ */
