//
// Created by Gregory Montilla on 2/22/18.
//

#ifndef LINKED_LISTS_ARRAYS_QUEUE_H
#define LINKED_LISTS_ARRAYS_QUEUE_H

template <class T>
class Queue {
public:
    Queue();
    void push(T item);
    T pop();
    bool empty();
    T front();
    void copy(Queue& queue);
    T print();
    T value(int i);
    int amount();

private:
    T queue[1000];
    int head;
    int tail;

};

template <class T>
Queue<T>::Queue() {
    head = 0;
    tail = 0;
}


template <class T>
T Queue<T>::pop() {
    int temp = head;
    head++;
    return queue[temp];
}

template <class T>
T Queue<T>::front() {
    return queue[head];
}

template <class T>
bool Queue<T>::empty() {
    return (head == tail);
}

template <class T>
void Queue<T>::push(T item) {
    queue[tail] = item;
    tail++;
}

template <class T>
void Queue<T>::copy(Queue& q) {
    for (int i = head; i < tail; i++) {
        q.push(queue[i]);
    }
}

template <class T>
T Queue<T>::print() {
    for (int i = head; i < tail; ++i) {
        std::cout << "[" << value(i) << "] -> ";
    }
    std::cout << "|||" << std::endl;
}

template <class T>
T Queue<T>::value(int i) {
    return queue[i];
}

template <class T>
int Queue<T>::amount() {
    return (tail-head);
}

#endif //LINKED_LISTS_ARRAYS_QUEUE_H
