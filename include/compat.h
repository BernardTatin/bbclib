/**
 * compat.h
 */

#if !defined(__compat_h__)
#define __compat_h__

#if defined(__WATCOMC__)
#define no_c11
#include "_compat/_default.h"
#elif defined(_MSC_VER)
#include "_compat/_msc.h"
#elif defined(__TURBOC__)
#define no_c11
#include "_compat/_default.h"
#else
#include "_compat/_default.h"
#endif

#endif
