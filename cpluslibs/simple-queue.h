/**
 * @file simple-queue.h
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

template <class T>
class Element {
    private:
        T *_value;
    public:
        Element(T *value) : _value(value) {
        }

        inline T *value() {
            return _value;
        }
};

template<class T>
class SQElement : public Element<T> {
    private:
        SQElement<T> *_next;
    public:
        SQElement(T *value) : Element<T>(value), _next(NULL) {
        }

        inline SQElement<T> *next() {
            return _next;
        }
        inline void set_next(SQElement<T> *next) {
            _next = next;
        }
};

template<class T>
class SimpleQueue {
    private:
        SQElement<T> *_input;
        SQElement<T> *_output;
        void _push(SQElement<T> *prt) {
            if (is_empty()) {
                _input = prt;
                _output = prt;
            } else {
                _input->set_next(prt);
                _input = prt;
            }
        }
        SQElement<T> *_pop(void) {
            if (is_empty()) {
                return NULL;
            } else {
                SQElement<T> *prt = _output;
                _output = _output->next();
                if (_output == NULL) {
                    _input = NULL;
                }
                return prt;
            }
        }
    public:

        SimpleQueue() :
            _input(NULL),
            _output(NULL) {
            }

        inline bool is_empty(void) {
            return _input == NULL || _output == NULL;
        }


        inline void push(T *t) {
            _push(new SQElement<T>(t));
        }

        inline T *pop() {
            SQElement<T> *prt = _pop();
            if (prt == NULL) {
                return NULL;
            } else {
                T *r = new T(*(prt->value()));
                delete prt->value();
                delete prt;
                return r;
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
