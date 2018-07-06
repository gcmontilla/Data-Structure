//
// Created by Gregory Montilla on 2/20/18.
//

#ifndef LINKED_LISTS_STACK_H
#define LINKED_LISTS_STACK_H

#include <iostream>
#include "list.h"
#include "stack.h"

using namespace std;

template <class T>

class Stack {

public:
    Stack():_top(NULL){}

    ~Stack();
    Stack(const Stack<T>& other);
    Stack<T>& operator =(const Stack<T>& rhs);

    void push(T item);
    T pop();
    T top();
    bool empty();
    friend ostream& operator << (ostream& outs, const Stack& s){
        return print_list(s._top, outs);
    }
private:
    node<T>* _top;
};


#endif //LINKED_LISTS_STACK_H
