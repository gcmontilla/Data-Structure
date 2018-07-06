//
// Created by Gregory Montilla on 4/3/18.
//

#ifndef HEAP_PQUEUE_H
#define HEAP_PQUEUE_H

#include "heap.h"
#include "info.h"

template <typename T>
class PQueue
{
public:
    PQueue();

    void insert(T value, int p);
    T Pop();

    void print_tree() const;
    friend ostream& operator <<(ostream& outs, const PQueue<T>& print_me) {
        print_me.print_tree();
        return outs;
    }

private:
    Heap<info<T> > heap;

};

template <typename T>
PQueue<T>::PQueue() {

}

/**
 * Inserts an item into the priority queue
 * @tparam T Datatype
 * @param value Value
 * @param p Priority
 */
template <typename T>
void PQueue<T>::insert(T value, int p) {
    heap.insert(info<T> (value, p));
}

/**
 * Pops item from priority queue
 * @tparam T Datatype
 * @return Restructured priority queue
 */
template <typename T>
T PQueue<T>::Pop() {
    heap.pop();
}

/**
 *
 * @tparam T
 */
template <typename T>
void PQueue<T>::print_tree() const {
    cout << heap;
}

#endif //HEAP_PQUEUE_H
