/**
 * compat.h
 */

#if !defined(__compat_h__)
#define __compat_h__

#if defined(__WATCOMC__)
#define no_c11
#elif defined(_MSC_VER)
#define no_c11
#elif defined(__TURBOC__)
#define no_c11
#endif

#include "_compat/_standard.h"

#endif
