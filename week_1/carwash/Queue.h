//
// Created by Gregory Montilla on 2/21/18.
//

#ifndef CARWASH_QUEUE_H
#define CARWASH_QUEUE_H

#include <iostream>
using namespace std;

template <class T>
class Queue {
private:
    struct node {
        T _data;
        node *next;
    };

    node *head;
    node *tail;
    int count;

public:
    // CONSTRUCTORS
    Queue();
    // DESTRUCTORS
    ~Queue();
    //
    void push(T data);
    T pop();
    T front();
    bool empty() const {
        return (count == 0);
    };


};

template <class T>
Queue<T>::Queue() {
    head = NULL;
    tail = NULL;
    count = 0;
}

template <class T>
Queue<T>::~Queue() {
}

template <class T>
void Queue<T>::push(T data) {
    node *Node;

    Node = new node;

    Node -> _data = data;
    Node -> next = NULL;

    if (!empty()) {
        head = Node;
        tail = Node;
    } else {
        tail -> next = Node;
        tail = Node;
    }

    count++;
}

template <class T>
T Queue<T>::pop() {
    T data = head -> _data;
    node *temp = head;
    head = head->next;
    delete temp;
    return data;

}

template <class T>
T Queue<T>::front() {
    T data = head -> _data;
    return data;
}

#endif //CARWASH_QUEUE_H
