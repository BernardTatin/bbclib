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
#if defined(__WATCOMC__) || defined(_MSC_VER)
#include <windows.h>
#else
#include <mutex>
#endif

class Lockable {
	private:
#if defined(__WATCOMC__) || defined(_MSC_VER)
		HANDLE _mtx;
#else
        std::mutex *_mtx;
#endif
	public:
		Lockable(): 
#if defined(__WATCOMC__) || defined(_MSC_VER)
			_mtx(CreateMutex(NULL, false, NULL))
#else
			_mtx(new std::mutex())
#endif
			{ }

		void lock() {
#if defined(__WATCOMC__) || defined(_MSC_VER)
			WaitForSingleObject(_mtx, INFINITE);
#else
			_mtx.lock();
#endif
		}

		void unlock() {
#if defined(__WATCOMC__) || defined(_MSC_VER)
			ReleaseMutex(_mtx);
#else
			_mtx.unlock();
#endif
		}
};

#endif /* __with_threads */

#endif /* __lockable_h__ */
