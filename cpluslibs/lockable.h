/**
 * @file lockable.h
 *
 * @date 17 juin 2014
 * @author bbfh
 *
 * @section description description
 * description du contenu du fichier
 */

#ifndef __lockable_h__
#define __lockable_h__

#if defined(__with_threads)
#include "common-defines.h"

class Lockable {
private:
    hMutex _mtx;
public:
    Lockable():
#if defined(__WATCOMC__) || defined(_MSC_VER)
    _mtx(CreateMutex(NULL, false, NULL))
#else
    _mtx(new std::mutex())
#endif
    {}

    inline void lock() {
#if defined(__WATCOMC__) || defined(_MSC_VER)
        WaitForSingleObject(_mtx, INFINITE);
#else
        _mtx.lock();
#endif
    }

    inline void unlock() {
#if defined(__WATCOMC__) || defined(_MSC_VER)
        ReleaseMutex(_mtx);
#else
        _mtx.unlock();
#endif
    }
};

#endif /* __with_threads */

#endif /* __lockable_h__ */
