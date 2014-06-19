/**
 * @file common-defines.h
 *
 * @date 19 juin 2014
 * @author bbfh
 *
 * @section description description
 * description du contenu du fichier
 */

#if !defined(__common_defines_h__)
#define __common_defines_h__

#if defined(__WATCOMC__) || defined(_MSC_VER)
#include <windows.h>
#else
#define _cplus11
#if defined(__with_threads)
#include <thread>
#include <mutex>
#endif
#endif

#if defined(__with_threads)
#if defined(_cplus11)
typedef std::mutex *hMutex;
#else
typedef HANDLE hMutex;
#endif
#endif

#endif // __common_defines_h__
