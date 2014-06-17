/**
 * @file simple-queue.h 
 * (project: asu-terminal)
 *
 * @date 17 juin 2014
 * @author bbfh
 *
 * @section description description
 * description du contenu du fichier
 */

#ifndef __simple_queue_h__
#define __simple_queue_h__

#if defined(__with_threads)
#include <mutex>
#endif

template<class T>
class SQElement {
	private:
		T *_next;
		T *_prev;
	protected:

	public:
		SQElement() :
			_next(NULL), _prev(NULL) {

			}
		inline T *next() {
			return _next;
		}
		inline T *prev() {
			return _prev;
		}
		inline void set_next(T *next) {
			_next = next;
		}
		inline void set_prev(T *prev) {
			_prev = prev;
		}
};

template<class T>
class SimpleQueue {
	protected:
		T *first;
		T *last;
	public:

		SimpleQueue() :
#if defined(__with_threads)
			_mtx(new std::mutex()), 
#endif
			first(NULL), 
			last(NULL) {
			}

		inline bool is_empty(void) {
			return first == NULL || last == NULL;
		}

		void push(T *prt) {
			if (is_empty()) {
				first = prt;
				last = prt;
			} else {
				first->set_prev(prt);
				prt->set_next(first);
				first = prt;
			}
		}


		T *pop(void) {
			if (is_empty()) {
				return NULL;
			} else {
				T *prt = last;
				last = last->prev();
				if (last != NULL) {
					last->set_next(NULL);
				} else {
					first = NULL;
				}
				return prt;
			}
		}

};

#if defined(__with_threads)
template<class T>
class SimpleQueueMT : public SimpleQueue<T> {
	private:
		std::mutex *_mtx;
	public:
		SimpleQueueMT() : SimpleQueue(), _mtx(new std::mutex()) {
		}

		bool is_empty(void) {
			bool r;
			lock_liste();
			r = SimpleQueue::is_empty();
			unlock_liste();
			return r;
		}

		void push(T *prt) {
			lock_liste();
			SimpleQueue::push(prt);
			unlock_liste();
		}

		T *pop(void) {
			T *prt;
			lock_liste();
			prt = SimpleQueue::pop();
			unlock_liste();
			return prt;
		}

		inline void lock_liste(void) {
			_mtx->lock();
		}

		inline void unlock_liste(void) {
			_mtx->unlock();
		}
}
#endif

#endif /* __simple_queue_h__ */
