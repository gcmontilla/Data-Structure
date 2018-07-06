//
// Created by Gregory Montilla on 2/20/18.
//

#ifndef LINKED_LISTS_QUEUE_H
#define LINKED_LISTS_QUEUE_H

#include <iostream>
#include "list.h"
using namespace std;

template <class T>
class Queue {

public:
    Queue(): _head(NULL), _tail(NULL) {}

    ~Queue();
    Queue(const Queue<T>& other);
    Queue<T> &operator = (const Queue &rhs);

    void push (T item);
    T pop();
    bool empty();
    T front();

    friend ostream& operator <<(ostream& outs, const Queue& q){
        return print_list(q._head, outs);
    }

private:
    node<T>* _head;
    node<T>* _tail;


};


#endif //LINKED_LISTS_QUEUE_H
