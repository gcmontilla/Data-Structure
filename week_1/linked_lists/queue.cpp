//
// Created by Gregory Montilla on 2/20/18.
//

#include "Headers/queue.h"

template <class T>
T Queue<T>::Queue() {

}

template <class T>
T Queue<T>::~Queue() {

}

template <class T>
T Queue<T>::Queue(const Queue<T> &other) {

}

template <class T>
T Queue<T>::operator=(const Queue &rhs) {}

template <class T>
T Queue<T>::push(T item) {
    _tail = item;
}

template <class T>
T Queue<T>::empty() {
    return (_head==NULL);
}

template <class T>
T Queue<T>::pop() {
    return _tail;
}

template <class T>
T Queue<T>::front() {
    return _head;

}