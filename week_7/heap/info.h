//
// Created by Gregory Montilla on 4/3/18.
//

#ifndef HEAP_INFO_H
#define HEAP_INFO_H

#include <iostream>

using namespace std;

template <typename T>
struct info {
    T item;
    int priority;

    info() {

    }
    info(T i, int p) {
        item = i;
        priority = p;
    }

    friend ostream& operator <<(ostream& outs, const info<T>& print_me) {
        return outs << "i[" << print_me.item << "] p[" << print_me.priority << "]" << endl;
    }

    friend bool operator <(const info<T>& lhs, const info<T>& rhs) {
        return lhs.priority < rhs.priority;
    }

    friend bool operator >(const info<T>& lhs, const info<T>& rhs) {
        return lhs.priority > rhs.priority;
    }

};

#endif //HEAP_INFO_H
