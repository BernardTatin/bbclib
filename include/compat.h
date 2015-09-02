/**
 * compat.h
 */

#if !defined(__compat_h__)
#define __compat_h__

#if defined(__WATCOMC__)
#include "_compat/_watcom.h"
#elif defined(_MSC_VER)
#include "_compat/_msc.h"
#else
#include "_compat/_default.h"
#endif

#endif
